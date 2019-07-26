exception MutationFailed(string);

module Mutation = [%relay.mutation
  {|
    mutation AddTodoMutation($input: AddTodoInput!) {
      addTodo(input: $input) {
        todoEdge {
          __typename
          cursor
          node {
            complete
            id
            text
          }
        }
        user {
          id
          totalCount
        }
      }
    }
  |}
];

let sharedUpdater = (~store, ~user, ~newEdge) => {
  open ReasonRelay;

  let userProxy =
    store->RecordSourceSelectorProxy.get(~dataId=makeDataId(user##id));

  let conn =
    switch (userProxy) {
    | Some(userProxy) =>
      ConnectionHandler.getConnection(
        ~record=userProxy,
        ~filters=None,
        ~key="TodoList_todos",
      )
    | None => None
    };

  switch (conn) {
  | Some(connection) =>
    ConnectionHandler.insertEdgeAfter(~connection, ~newEdge, ~cursor=None)
  | None => ()
  };
};

let tempID = ref(0);

let incrementTempId = () => tempID := tempID^ + 1;

let commit = (~environment, ~text, ~user) => {
  incrementTempId();

  Mutation.commitMutation(
    ~environment,
    ~variables={
      "input": {
        "text": text,
        "userId": user##userId,
        "clientMutationId": Some(string_of_int(tempID^)),
      },
    },
    ~updater=
      store => {
        open ReasonRelay;

        let payload =
          store->RecordSourceSelectorProxy.getRootField(~fieldName="addTodo");

        switch (payload) {
        | Some(payload) =>
          switch (
            payload->RecordProxy.getLinkedRecord(
              ~name="todoEdge",
              ~arguments=None,
            )
          ) {
          | Some(newEdge) => sharedUpdater(~store, ~user, ~newEdge)
          | None => ()
          }
        | None => ()
        };
      },
    ~optimisticUpdater=
      store => {
        open ReasonRelay;

        incrementTempId();

        let id = "client:newTodo" ++ string_of_int(tempID^);

        let node =
          store->RecordSourceSelectorProxy.create(
            ~dataId=makeDataId(id),
            ~typeName="Todo",
          );

        node
        ->RecordProxy.setValueString(
            ~value=text,
            ~name="text",
            ~arguments=None,
          )
        ->RecordProxy.setValueString(~value=id, ~name="id", ~arguments=None)
        ->ignore;

        let newEdge =
          store->RecordSourceSelectorProxy.create(
            ~dataId=makeDataId("client:newEdge:" ++ string_of_int(tempID^)),
            ~typeName="TodoEdge",
          );

        newEdge
        ->RecordProxy.setLinkedRecord(
            ~record=node,
            ~name="node",
            ~arguments=None,
          )
        ->ignore;

        sharedUpdater(~store, ~user, ~newEdge);

        let userProxy =
          store->RecordSourceSelectorProxy.get(~dataId=makeDataId(user##id));

        switch (userProxy) {
        | Some(userProxy) =>
          let maybeTotalCount =
            userProxy->RecordProxy.getValueInt(
              ~name="totalCount",
              ~arguments=None,
            );

          switch (maybeTotalCount) {
          | Some(totalCount) =>
            userProxy
            ->RecordProxy.setValueInt(
                ~name="totalCount",
                ~value=totalCount + 1,
                ~arguments=None,
              )
            ->ignore
          | None => raise(MutationFailed("Could not find totalCount."))
          };
        | None => raise(MutationFailed("Failed to retrieve userProxy."))
        };
      },
    (),
  );
};
