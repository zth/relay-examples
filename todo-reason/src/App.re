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

    switch (query) {
    | Loading => <div> {React.string("Loading")} </div>
    | Error(e) =>
      <div>
        {React.string(
           Belt.Option.getWithDefault(
             Js.Exn.message(e),
             "Something went wrong!",
           ),
         )}
      </div>
    | Data(data) =>
      switch (data##user |> Js.Nullable.toOption) {
      | Some(user) => <TodoApp user />
      | None => React.string("Something went wrong!")
      }
    };
  };
};

ReactDOMRe.renderToElementWithId(
  <ReasonRelay.Context.Provider environment=RelayEnv.environment>
    <AppDisplayer />
  </ReasonRelay.Context.Provider>,
  "root",
);
