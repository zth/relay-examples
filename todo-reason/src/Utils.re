let makeClassNames = classNames =>
  classNames
  |> List.map(((className, included)) => included ? className ++ " " : "")
  |> String.concat(" ");

let collectConnectionNodesFromNullable = obj =>
  switch (obj |> Js.Nullable.toOption) {
  | Some(obj) => ReasonRelayUtils.collectConnectionNodes(obj)
  | None => [||]
  };