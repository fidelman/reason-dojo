/* module Style = {

}; */

module ComposableMap = {
  [@bs.deriving abstract]
  type projectionConfigT= {
    scale: int,
    rotation: (int, int, int)
  };

  [@bs.deriving abstract]
  type props = {
    height: int,
    width: int,
    projectionConfig: projectionConfigT,
    style: ReactDOMRe.Style.t
  };

  [@bs.module "react-simple-maps"]
  external composableMap : ReasonReact.reactClass = "ComposableMap";
  let make = (~height, ~width, ~projectionConfig, ~style, children) => {
    ReasonReact.wrapJsForReason(
      ~reactClass=composableMap,
      ~props=props(
        ~height,
        ~width,
        ~projectionConfig=projectionConfigT(~scale=scale(projectionConfig), ~rotation=rotation(projectionConfig)),
        ~style
      ),
      children
    );
  };
};

module ZoomableGroup = {
  [@bs.deriving abstract]
  type props = {
    center: (int, int),
    disablePanning: bool
  };
  [@bs.module "react-simple-maps"]
  external zoomableGroup : ReasonReact.reactClass = "ZoomableGroup";
  let make = (~center, ~disablePanning, children) =>
    ReasonReact.wrapJsForReason(
      ~reactClass=zoomableGroup,
      ~props=props(
        ~center,
        ~disablePanning
      ),
      children
    )
};

module Geographies = {
  [@bs.deriving abstract]
  type props = {
    geography: string
  };

  [@bs.module "react-simple-maps"]
  external geographies : ReasonReact.reactClass = "Geographies";
  let make = (~geography, children) =>
    ReasonReact.wrapJsForReason(
      ~reactClass=geographies,
      ~props=props(
        ~geography
      ),
      children
    )
};

module Geography = {
  type geographyT;
  type projectionT;
  
  [@bs.deriving abstract]
  type styleT = {
    default: ReactDOMRe.Style.t,
    hover: ReactDOMRe.Style.t,
    pressed: ReactDOMRe.Style.t
  };

  [@bs.deriving abstract]
  type props = {
    geography: geographyT,
    projection: projectionT,
    style: styleT
  };

  [@bs.module "react-simple-maps"]
  external geographyJs : ReasonReact.reactClass = "Geography";
  let make = (~geography, ~projection, ~style, children) =>
    ReasonReact.wrapJsForReason(
      ~reactClass=geographyJs,
      ~props=props(
        ~geography,
        ~projection,
        ~style
      ),
      children
    )
}

module Markers = {
  [@bs.module "react-simple-maps"]
  external markers : ReasonReact.reactClass = "Markers";
  let make = (children) =>
    ReasonReact.wrapJsForReason(
      ~reactClass=markers,
      ~props = Js.Obj.empty,
      children
    )
}

module Marker = {
  [@bs.deriving abstract]
  type markerT = {
    coordinates: (float, float)
  };

  [@bs.deriving abstract]
  type props = {
    marker: markerT
  };

  [@bs.module "react-simple-maps"]
  external js : ReasonReact.reactClass = "Marker";
  let make = (~marker, children) =>
    ReasonReact.wrapJsForReason(
      ~reactClass=js,
      ~props=props(
        ~marker=markerT(~coordinates=coordinates(marker)),
      ),
      children
    )
};

module Annotations = {
  [@bs.module "react-simple-maps"]
  external annotations : ReasonReact.reactClass = "Annotations";
  let make = (children) =>
    ReasonReact.wrapJsForReason(
      ~reactClass=annotations,
      ~props = Js.Obj.empty,
      children
    )
};

module Annotation = {
  [@bs.deriving abstract]
  type props = {
    subject: (float, float),
    dx: int,
    dy: int,
    strokeWidth: int
  };

  [@bs.module "react-simple-maps"]
  external annotation : ReasonReact.reactClass = "Annotation";
  let make = (~subject, ~dx, ~dy, ~strokeWidth, children) =>
    ReasonReact.wrapJsForReason(
      ~reactClass=annotation,
      ~props=props(
        ~subject,
        ~dx,
        ~dy,
        ~strokeWidth
      ),
      children
    )
};

type state = array(Fetcher.data);

type actions = | Update(array(Fetcher.data));

let component = ReasonReact.reducerComponent("Map");

let make = (_children) => {
  ...component,
  initialState: () => [||],
  reducer: (action, _state) =>
    switch (action) {
    | Update(users) => ReasonReact.Update(users)
    },
  didMount: (self) => {
    /* TODO: Set Interval */
    let urlGet = "https://immense-river-25513.herokuapp.com/locations";

    let rec fetch = () => {
      Fetcher.fetchGet(~url = urlGet, ~cb = (data) => {
        self.send(Update(data));

        Js.Global.setTimeout(fetch, 5000) |> ignore;
      });
    };

    fetch();

    

    let urlPost = "https://immense-river-25513.herokuapp.com/add-location";
    let body = "fidelman";
    Fetcher.fetchPost(~url = urlPost, ~body);
  },
  render: self =>
    <div style={ReactDOMRe.Style.make(
      ~width = "100%",
      ~maxWidth = "980",
      ~margin = "0 auto",
      ()
    )}>
      <ComposableMap
        width={980}
        height={551}
        projectionConfig={ComposableMap.projectionConfigT(
          ~scale=205,
          ~rotation=(-11, 0, 0)
        )}
        style={ReactDOMRe.Style.make(
          ~width="100%",
          ~height="auto",
        ())}
      >
        <ZoomableGroup
          center={(0, 20)}
          disablePanning={true}
        >
          <Geographies geography="/world-50m.json">
            {(geographies, projection) => Array.mapi((i, geography) => {
              <Geography
                key={string_of_int(i)}
                geography={geography}
                projection={projection}
                style={Geography.styleT(
                  ~default=ReactDOMRe.Style.make(
                    ~fill = "#ECEFF1",
                    ~stroke = "#607D8B",
                    ~strokeWidth = "0.75",
                    ~outline = "none",
                  ()),
                  ~hover=ReactDOMRe.Style.make(
                    ~fill = "#607D8B",
                    ~stroke = "#607D8B",
                    ~strokeWidth = "0.75",
                    ~outline = "none",
                  ()),
                  ~pressed=ReactDOMRe.Style.make(
                    ~fill = "#FF5722",
                    ~stroke = "#607D8B",
                    ~strokeWidth = "0.75",
                    ~outline = "none",
                  ())
                )}
              />
            }, geographies)}
          </Geographies>
          <Markers>
            {Array.mapi((i, user: Fetcher.data) => {
              let (lat, lng) = Fetcher.location(user);
              <Marker key={string_of_int(i)} marker={Marker.markerT(
                ~coordinates=(lng, lat)
              )}>
                <circle fill={"red"} cx={"0"} cy={"0"} r={"3"} />
              </Marker>
            }, self.state)}
          </Markers>
          <Annotations>
            {Array.mapi((i, user: Fetcher.data) => {
                let (lat, lng) = Fetcher.location(user);
                <Annotation
                  key={string_of_int(i)}
                  dx={-30}
                  dy={30}
                  subject={(lng, lat)}
                  strokeWidth={1}
                  >
                  <text>
                    {ReasonReact.string(Fetcher.username(user))}
                  </text>
                </Annotation>
              }, self.state)}
          </Annotations>
        </ZoomableGroup>
      </ComposableMap>
    </div>,
};