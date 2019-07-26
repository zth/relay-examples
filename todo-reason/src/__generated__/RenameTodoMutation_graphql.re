module Unions = {};
type input_RenameTodoInput = {
  .
  "id": string,
  "text": string,
  "clientMutationId": option(string),
};
type variables = {. "input": input_RenameTodoInput};
type response = {
  .
  "renameTodo":
    Js.Nullable.t({
      .
      "todo": {
        .
        "id": string,
        "text": string,
      },
    }),
};

let node: ReasonRelay.mutationNode = [%bs.raw
  {| (function(){
var v0 = [
  {
    "kind": "LocalArgument",
    "name": "input",
    "type": "RenameTodoInput!",
    "defaultValue": null
  }
],
v1 = [
  {
    "kind": "LinkedField",
    "alias": null,
    "name": "renameTodo",
    "storageKey": null,
    "args": [
      {
        "kind": "Variable",
        "name": "input",
        "variableName": "input"
      }
    ],
    "concreteType": "RenameTodoPayload",
    "plural": false,
    "selections": [
      {
        "kind": "LinkedField",
        "alias": null,
        "name": "todo",
        "storageKey": null,
        "args": null,
        "concreteType": "Todo",
        "plural": false,
        "selections": [
          {
            "kind": "ScalarField",
            "alias": null,
            "name": "id",
            "args": null,
            "storageKey": null
          },
          {
            "kind": "ScalarField",
            "alias": null,
            "name": "text",
            "args": null,
            "storageKey": null
          }
        ]
      }
    ]
  }
];
return {
  "kind": "Request",
  "fragment": {
    "kind": "Fragment",
    "name": "RenameTodoMutation",
    "type": "Mutation",
    "metadata": null,
    "argumentDefinitions": (v0/*: any*/),
    "selections": (v1/*: any*/)
  },
  "operation": {
    "kind": "Operation",
    "name": "RenameTodoMutation",
    "argumentDefinitions": (v0/*: any*/),
    "selections": (v1/*: any*/)
  },
  "params": {
    "operationKind": "mutation",
    "name": "RenameTodoMutation",
    "id": null,
    "text": "mutation RenameTodoMutation(\n  $input: RenameTodoInput!\n) {\n  renameTodo(input: $input) {\n    todo {\n      id\n      text\n    }\n  }\n}\n",
    "metadata": {}
  }
};
})() |}
];
