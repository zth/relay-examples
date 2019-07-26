module Mutation = [%relay.mutation
  {|
  mutation ChangeTodoStatusMutation($input: ChangeTodoStatusInput!) {
    changeTodoStatus(input: $input) {
      todo {
        id
        complete
      }
      user {
        id
        completedCount
      }
    }
  }
|}
];

let commit = (~environment, ~complete, ~todo, ~user) =>
  Mutation.commitMutation(
    ~environment,
    ~variables={
      "input": {
        "clientMutationId": None,
        "complete": complete,
        "userId": user##userId,
        "id": todo##id,
      },
    },
    ~optimisticResponse={
      "changeTodoStatus":
        Some({
          "todo": {
            "complete": complete,
            "id": todo##id,
          },
          "user": {
            "id": user##id,
            "completedCount":
              complete ? user##completedCount + 1 : user##completedCount - 1,
          },
        })
        |> Js.Nullable.fromOption,
    },
    (),
  );
