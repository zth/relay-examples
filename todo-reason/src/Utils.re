let makeClassNames = classNames =>
  classNames
  |> List.map(((className, included)) => included ? className ++ " " : "")
  |> String.concat(" ");
