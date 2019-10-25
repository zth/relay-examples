module Query = [%relay.query
  {|
    query AppQuery($userId: String) {
      user(id: $userId) {
        ...TodoApp_user
      }
    }
|}
];

module AppDisplayer = {
  [@react.component]
  let make = () => {
    let query = Query.use(~variables={"userId": Some("me")}, ());

    switch (query##user |> Js.Nullable.toOption) {
    | Some(user) => <TodoApp user />
    | None => React.string("Something went wrong!")
    };
  };
};

ReactDOMRe.renderToElementWithId(
  <ReasonRelay.Context.Provider environment=RelayEnv.environment>
    <React.Suspense fallback={<div> {React.string("Loading...")} </div>}>
      <AppDisplayer />
    </React.Suspense>
  </ReasonRelay.Context.Provider>,
  "root",
);