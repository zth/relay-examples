module TodoFragment = [%relay.fragment
  {|
    fragment Todo_todo on Todo {
      complete
      id
      text
    }
  |}
];

module UserFragment = [%relay.fragment
  {|
    fragment Todo_user on User {
      id
      userId
      totalCount
      completedCount
    }
  |}
];

[@react.component]
let make = (~user as userRef, ~todo as todoRef) => {
  let user = UserFragment.use(userRef);
  let todo = TodoFragment.use(todoRef);
  let environment = ReasonRelay.useEnvironmentFromContext();

  let (isEditing, setIsEditing) = React.useState(() => false);

  let handleCompleteChange = e => {
    let complete = ReactEvent.Form.currentTarget(e)##checked;
    ChangeTodoStatusMutation.commit(~environment, ~complete, ~todo, ~user)
    |> ignore;
  };

  let removeTodo = () =>
    RemoveTodoMutation.commit(~environment, ~todo, ~user) |> ignore;

  let handleDestroyClick = _ => removeTodo();
  let handleLabelDoubleClick = _ => setIsEditing(_ => true);
  let handleTextInputCancel = _ => setIsEditing(_ => false);

  let handleTextInputDelete = _ => {
    setIsEditing(_ => false);
    removeTodo();
  };

  let handleTextInputSave = text => {
    setIsEditing(_ => false);
    RenameTodoMutation.commit(~environment, ~text, ~todo) |> ignore;
  };

  <li
    className={Utils.makeClassNames([
      ("completed", todo##complete),
      ("editing", isEditing),
    ])}>
    <div className="view">
      <input
        checked={todo##complete}
        className="toggle"
        onChange=handleCompleteChange
        type_="checkbox"
      />
      <label onDoubleClick=handleLabelDoubleClick>
        {React.string(todo##text)}
      </label>
      <button className="destroy" onClick=handleDestroyClick />
    </div>
    {isEditing
       ? <TodoTextInput
           className="edit"
           commitOnBlur=true
           initialValue=todo##text
           onCancel=handleTextInputCancel
           onDelete=handleTextInputDelete
           onSave=handleTextInputSave
         />
       : React.null}
  </li>;
};
