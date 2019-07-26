exception MutationFailed(string);

module Mutation = [%relay.mutation
  {|
  mutation RemoveTodoMutation($input: RemoveTodoInput!) {
    removeTodo(input: $input) {
      deletedTodoId
      user {
        completedCount
        totalCount
      }
    }
  }
|}
];

let sharedUpdater = (~store, ~user, ~deletedID) => {
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
      ConnectionHandler.deleteNode(
        ~connection,
        ~nodeId=makeDataId(deletedID),
      )
    | None => ()
    }
  | None => ()
  };
};

let commit = (~environment, ~todo, ~user) => {
  Mutation.commitMutation(
    ~environment,
    ~variables={
      "input": {
        "clientMutationId": None,
        "id": todo##id,
        "userId": user##userId,
      },
    },
    ~updater=
      store =>
        ReasonRelay.(
          switch (
            store->RecordSourceSelectorProxy.getRootField(
              ~fieldName="removeTodo",
            )
          ) {
          | None =>
            raise(MutationFailed("Could not find removeTodo root field."))
          | Some(payload) =>
            switch (
              payload->RecordProxy.getValueString(
                ~name="deletedTodoId",
                ~arguments=None,
              )
            ) {
            | Some(deletedID) => sharedUpdater(~store, ~user, ~deletedID)
            | None => raise(MutationFailed("Could not find deletedTodoId."))
            }
          }
        ),
    (),
  );
};
