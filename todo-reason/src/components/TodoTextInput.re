[@react.component]
let make =
    (
      ~className,
      ~commitOnBlur=?,
      ~initialValue=?,
      ~onCancel=?,
      ~onDelete=?,
      ~onSave,
      ~placeholder=?,
    ) => {
  let theInitialValue = Belt.Option.getWithDefault(initialValue, "");

  let (text, setText) = React.useState(() => theInitialValue);

  let inputRef = React.useRef(Js.Nullable.null);

  React.useEffect1(
    () => {
      switch (inputRef |> React.Ref.current |> Js.Nullable.toOption) {
      | Some(input) => ReactDOMRe.domElementToObj(input)##focus()
      | None => ()
      };

      None;
    },
    [|inputRef|],
  );

  let commitChanges = () => {
    let newText = text |> String.trim;

    switch (onDelete, onCancel, newText) {
    | (Some(onDelete), _, "") => onDelete()
    | (_, Some(onCancel), newText) when newText == theInitialValue =>
      onCancel()
    | (_, _, newText) when newText != "" =>
      onSave(newText);
      setText(_ => "");
    | _ => ()
    };
  };

  let handleBlur = _ =>
    switch (commitOnBlur) {
    | Some(true) => commitChanges()
    | Some(false)
    | None => ()
    };

  let handleChange = e => {
    let newText = ReactEvent.Form.currentTarget(e)##value;
    setText(_ => newText);
  };

  let handleKeyDown = e =>
    switch (ReactEvent.Keyboard.keyCode(e), onCancel) {
    | (27, Some(onCancel)) => onCancel()
    | (13, _) => commitChanges()
    | _ => ()
    };

  <input
    className
    type_="text"
    onBlur=handleBlur
    onChange=handleChange
    onKeyDown=handleKeyDown
    placeholder={Belt.Option.getWithDefault(placeholder, "")}
    value=text
    ref={ReactDOMRe.Ref.domRef(inputRef)}
  />;
};
