module UserFragment = [%relay.fragment
  {|
    fragment TodoApp_user on User {
      id
      userId
      totalCount
      ...TodoListFooter_user
      ...TodoList_user
    }
  |}
];

[@react.component]
let make = (~user as userRef) => {
  let user = UserFragment.use(userRef);
  let environment = ReasonRelay.useEnvironmentFromContext();

  let handleTextInputSave = text =>
    AddTodoMutation.commit(~environment, ~text, ~user);

  let hasTodos = user##totalCount > 0;

  <div>
    <section className="todoapp">
      <header className="header"> <h1> {React.string("todos")} </h1> </header>
      <TodoTextInput
        className="new-todo"
        onSave=handleTextInputSave
        placeholder="What needs to be done?"
      />
      <TodoList user />
      {hasTodos ? <TodoListFooter user /> : React.null}
    </section>
    <footer className="info">
      <p> {React.string("Double-click to edit a todo")} </p>
      <p> {React.string("Created by the Relay community")} </p>
      <p>
        {React.string("Part of ")}
        <a href="http://todomvc.com"> {React.string("TodoMVC")} </a>
      </p>
    </footer>
  </div>;
};
