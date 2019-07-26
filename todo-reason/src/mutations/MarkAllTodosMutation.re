module Mutation = [%relay.mutation
  {|
  mutation MarkAllTodosMutation($input: MarkAllTodosInput!) {
    markAllTodos(input: $input) {
      changedTodos {
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

let commit = (~environment, ~complete, ~todos, ~user) => {
  Mutation.commitMutation(
    ~environment,
    ~variables={
      "input": {
        "clientMutationId": None,
        "complete": complete,
        "userId": user##userId,
      },
    },
    ~optimisticResponse={
      "markAllTodos":
        Some({
          "changedTodos":
            Some(
              ReasonRelayUtils.collectConnectionNodes(todos)
              ->Belt.Array.keepMap(node =>
                  node##complete != complete
                    ? Some({"complete": complete, "id": node##id}) : None
                ),
            )
            |> Js.Nullable.fromOption,
          "user": {
            "id": user##id,
            "completedCount": complete ? user##totalCount : 0,
          },
        })
        |> Js.Nullable.fromOption,
    },
    (),
  );
};
