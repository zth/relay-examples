module UserFragment = [%relay.fragment
  {|
    fragment TodoListFooter_user on User {
      id
      userId
      completedCount
      todos(
        first: 2147483647 # max GraphQLInt
      ) @connection(key: "TodoList_todos") {
        edges {
          node {
            id
            complete
          }
        }
      }
      totalCount
    }
|}
];

[@react.component]
let make = (~user as userRef) => {
  let user = UserFragment.use(userRef);

  let environment = ReasonRelay.useEnvironmentFromContext();

  let completedTodos =
    Utils.collectConnectionNodesFromNullable(user##todos)
    ->Belt.Array.keepMap(node => node##complete ? Some(node) : None);

  let handleRemoveCompletedTodosClick = _ =>
    RemoveCompletedTodosMutation.commit(~environment, ~user, ~completedTodos)
    |> ignore;

  let numRemainingTodos = user##totalCount - user##completedCount;

  <footer className="footer">
    <span className="todo-count">
      <strong> {numRemainingTodos |> string_of_int |> React.string} </strong>
      {React.string(" item")}
      {numRemainingTodos == 1 ? React.null : React.string("s")}
      {React.string(" left")}
    </span>
    {user##completedCount > 0
       ? <button
           className="clear-completed" onClick=handleRemoveCompletedTodosClick>
           {React.string("Clear completed")}
         </button>
       : React.null}
  </footer>;
};