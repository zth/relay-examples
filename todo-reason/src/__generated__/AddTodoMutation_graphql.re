module Unions = {};
type input_AddTodoInput = {
  .
  "text": string,
  "userId": string,
  "clientMutationId": option(string),
};
type variables = {. "input": input_AddTodoInput};
type response = {
  .
  "addTodo":
    Js.Nullable.t({
      .
      "todoEdge": {
        .
        "__typename": string,
        "cursor": string,
        "node":
          Js.Nullable.t({
            .
            "complete": bool,
            "id": string,
            "text": string,
          }),
      },
      "user": {
        .
        "id": string,
        "totalCount": int,
      },
    }),
};

let node: ReasonRelay.mutationNode = [%bs.raw
  {| (function(){
var v0 = [
  {
    "kind": "LocalArgument",
    "name": "input",
    "type": "AddTodoInput!",
    "defaultValue": null
  }
],
v1 = {
  "kind": "ScalarField",
  "alias": null,
  "name": "id",
  "args": null,
  "storageKey": null
},
v2 = [
  {
    "kind": "LinkedField",
    "alias": null,
    "name": "addTodo",
    "storageKey": null,
    "args": [
      {
        "kind": "Variable",
        "name": "input",
        "variableName": "input"
      }
    ],
    "concreteType": "AddTodoPayload",
    "plural": false,
    "selections": [
      {
        "kind": "LinkedField",
        "alias": null,
        "name": "todoEdge",
        "storageKey": null,
        "args": null,
        "concreteType": "TodoEdge",
        "plural": false,
        "selections": [
          {
            "kind": "ScalarField",
            "alias": null,
            "name": "__typename",
            "args": null,
            "storageKey": null
          },
          {
            "kind": "ScalarField",
            "alias": null,
            "name": "cursor",
            "args": null,
            "storageKey": null
          },
          {
            "kind": "LinkedField",
            "alias": null,
            "name": "node",
            "storageKey": null,
            "args": null,
            "concreteType": "Todo",
            "plural": false,
            "selections": [
              {
                "kind": "ScalarField",
                "alias": null,
                "name": "complete",
                "args": null,
                "storageKey": null
              },
              (v1/*: any*/),
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
      },
      {
        "kind": "LinkedField",
        "alias": null,
        "name": "user",
        "storageKey": null,
        "args": null,
        "concreteType": "User",
        "plural": false,
        "selections": [
          (v1/*: any*/),
          {
            "kind": "ScalarField",
            "alias": null,
            "name": "totalCount",
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
    "name": "AddTodoMutation",
    "type": "Mutation",
    "metadata": null,
    "argumentDefinitions": (v0/*: any*/),
    "selections": (v2/*: any*/)
  },
  "operation": {
    "kind": "Operation",
    "name": "AddTodoMutation",
    "argumentDefinitions": (v0/*: any*/),
    "selections": (v2/*: any*/)
  },
  "params": {
    "operationKind": "mutation",
    "name": "AddTodoMutation",
    "id": null,
    "text": "mutation AddTodoMutation(\n  $input: AddTodoInput!\n) {\n  addTodo(input: $input) {\n    todoEdge {\n      __typename\n      cursor\n      node {\n        complete\n        id\n        text\n      }\n    }\n    user {\n      id\n      totalCount\n    }\n  }\n}\n",
    "metadata": {}
  }
};
})() |}
];
