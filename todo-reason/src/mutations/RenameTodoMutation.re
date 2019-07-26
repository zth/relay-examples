module Mutation = [%relay.mutation
  {|
  mutation RenameTodoMutation($input: RenameTodoInput!) {
    renameTodo(input: $input) {
      todo {
        id
        text
      }
    }
  }
|}
];

let commit = (~environment, ~text, ~todo) =>
  Mutation.commitMutation(
    ~environment,
    ~variables={
      "input": {
        "clientMutationId": None,
        "text": text,
        "id": todo##id,
      },
    },
    ~optimisticResponse={
      "renameTodo":
        Some({
          "todo": {
            "id": todo##id,
            "text": text,
          },
        })
        |> Js.Nullable.fromOption,
    },
    (),
  );
