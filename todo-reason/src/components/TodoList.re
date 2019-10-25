module UserFragment = [%relay.fragment
  {|
    fragment TodoList_user on User {
    todos(
      first: 2147483647 # max GraphQLInt
    ) @connection(key: "TodoList_todos") {
      edges {
        node {
          id
          complete
          ...Todo_todo
        }
      }
    }
    id
    userId
    totalCount
    completedCount
    ...Todo_user
    }
|}
];

[@react.component]
let make = (~user as userRef) => {
  let user = UserFragment.use(userRef);
  let environment = ReasonRelay.useEnvironmentFromContext();

  let handleMarkAllChange = e => {
    let complete = ReactEvent.Form.currentTarget(e)##checked;

    switch (user##todos |> Js.Nullable.toOption) {
    | Some(todos) =>
      MarkAllTodosMutation.commit(~environment, ~complete, ~todos, ~user)
      |> ignore
    | None => ()
    };
  };

  <section className="main">
    <input
      checked={user##totalCount == user##completedCount}
      className="toggle-all"
      onChange=handleMarkAllChange
      type_="checkbox"
    />
    <label htmlFor="toggle-all">
      {React.string("Mark all as complete")}
    </label>
    <ul className="todo-list">
      {user##todos
       |> Utils.collectConnectionNodesFromNullable
       |> Array.map(node => <Todo key={node##id} todo=node user />)
       |> React.array}
    </ul>
  </section>;
};