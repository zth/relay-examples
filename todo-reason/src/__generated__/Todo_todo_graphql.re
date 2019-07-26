module Unions = {};
type fragment = {
  .
  "complete": bool,
  "id": string,
  "text": string,
};

type t;
type fragmentRef;
type fragmentRefSelector('a) = {.. "__$fragment_ref__Todo_todo": t} as 'a;
external getFragmentRef: fragmentRefSelector('a) => fragmentRef = "%identity";

let node: ReasonRelay.fragmentNode = [%bs.raw
  {| {
  "kind": "Fragment",
  "name": "Todo_todo",
  "type": "Todo",
  "metadata": null,
  "argumentDefinitions": [],
  "selections": [
    {
      "kind": "ScalarField",
      "alias": null,
      "name": "complete",
      "args": null,
      "storageKey": null
    },
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
} |}
];
