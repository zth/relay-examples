module Mutation = [%relay.mutation
  {|
  mutation RemoveCompletedTodosMutation($input: RemoveCompletedTodosInput!) {
    removeCompletedTodos(input: $input) {
      deletedTodoIds
      user {
        completedCount
        totalCount
      }
    }
  }
|}
];

let sharedUpdater = (~store, ~user, ~deletedIDs) => {
  open ReasonRelay;

  let userProxy =
    store->RecordSourceSelectorProxy.get(~dataId=makeDataId(user##id));

  switch (userProxy) {
  | Some(userProxy) =>
    switch (
      ConnectionHandler.getConnection(
        ~record=userProxy,
        ~key="TodoList_todos",
        ~filters=None,
      )
    ) {
    | Some(connection) =>
      deletedIDs
      |> Array.iter(id =>
           ConnectionHandler.deleteNode(~connection, ~nodeId=makeDataId(id))
         )
    | None => ()
    }
  | None => ()
  };
};

let commit = (~environment, ~completedTodos, ~user) =>
  Mutation.commitMutation(
    ~environment,
    ~variables={
      "input": {
        "userId": user##userId,
        "clientMutationId": None,
      },
    },
    ~updater=
      store => {
        open ReasonRelay;

        let payload =
          store->RecordSourceSelectorProxy.getRootField(
            ~fieldName="removeCompletedTodos",
          );

        let deletedIDs =
          switch (payload) {
          | Some(payload) =>
            Belt.Option.getWithDefault(
              payload->RecordProxy.getValueStringArray(
                ~name="deletedTodoIds",
                ~arguments=None,
              ),
              [||],
            )
            ->Belt.Array.keepMap(value => value)
          | None => [||]
          };

        sharedUpdater(~store, ~user, ~deletedIDs);
      },
    ~optimisticUpdater=
      store => {
        let completedNodeIds =
          completedTodos->Belt.Array.keepMap(node =>
            node##complete ? Some(node##id) : None
          );

        sharedUpdater(~store, ~user, ~deletedIDs=completedNodeIds);
      },
    (),
  );
