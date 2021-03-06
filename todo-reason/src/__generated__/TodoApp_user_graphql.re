type t;
type fragmentRef;
type fragmentRefSelector('a) = {.. "__$fragment_ref__TodoApp_user": t} as 'a;
external getFragmentRef: fragmentRefSelector('a) => fragmentRef = "%identity";

type fragment = {
  .
  "__$fragment_ref__TodoList_user": TodoList_user_graphql.t,
  "__$fragment_ref__TodoListFooter_user": TodoListFooter_user_graphql.t,
  "totalCount": int,
  "userId": string,
  "id": string,
};
type operationType = ReasonRelay.fragmentNode;

module Unions = {};

let node: operationType = [%bs.raw
  {| {
  "kind": "Fragment",
  "name": "TodoApp_user",
  "type": "User",
  "metadata": null,
  "argumentDefinitions": [],
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
      "name": "userId",
      "args": null,
      "storageKey": null
    },
    {
      "kind": "ScalarField",
      "alias": null,
      "name": "totalCount",
      "args": null,
      "storageKey": null
    },
    {
      "kind": "FragmentSpread",
      "name": "TodoListFooter_user",
      "args": null
    },
    {
      "kind": "FragmentSpread",
      "name": "TodoList_user",
      "args": null
    }
  ]
} |}
];
