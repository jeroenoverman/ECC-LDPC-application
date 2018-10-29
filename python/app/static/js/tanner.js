var messageContainer = document.getElementById("messages");
function WebSocketTest() {
    var messageContainer = document.getElementById("messages");
    if ("WebSocket" in window) {
        messageContainer.innerHTML = "WebSocket is supported by your Browser!" + window.location.hostname;
        var ws = new WebSocket("ws://" + window.location.hostname + ":8080/ws/");
        ws.onopen = function() {
        };
        ws.onmessage = function (evt) {
            var received_msg = evt.data;
            messageContainer.innerHTML += "<br /><hr />Message is received...<br /><i>" + received_msg + "</i>";
        };
        ws.onclose = function() {
            messageContainer.innerHTML = "Connection is closed...";
        };
    } else {
        messageContainer.innerHTML = "WebSocket NOT supported by your Browser!";
    }
}

$(function() {
    var cy = window.cy = cytoscape({
      container: document.getElementById('cy'),

      boxSelectionEnabled: false,
      autounselectify: true,
      zoomingEnabled: true,
      panningEnabled: true,
      userZoomingEnabled: true,
      userPanningEnabled: true,
      layout: {
        name: 'grid', 
        rows:2,
        cols:10,
        fit: true,
        //padding: 20,
        //zoomLevel: 2.5
      },

      style: [
        {
          selector: 'node',
          style: {
            'content': 'data(id)',
            'text-opacity': 1,
            'color': 'white',
            'text-valign': 'center',
            'text-halign': 'center',
            'height': 30,
            'width': 30//,
            //'background-color': '#337ab7'
          }
        },

        {
          selector: 'edge',
          style: {
            'curve-style': 'haystack',
            'haystack-radius': 0,
            'width': 2,
            'opacity': 0.5//,
            //'line-color': '#337ab7'
          }
        }
      ],

      elements: [

        {
          data: {
            id: "v0",
            name: "v0"
          },
          position: {
            x: 30,
            y: 30
          },
          group: "nodes",
          removed: false,
          selected: false,
          selectable: false,
          locked: false,
          grabbable: false,
          classes: ""
        },
        {
          data: {
            id: "v1",
            name: "v1"
          },
          position: {
            x: 100,
            y: 30
          },
          group: "nodes",
          removed: false,
          selected: false,
          selectable: false,
          locked: false,
          grabbable: false,
          classes: ""
        },
        {
          data: {
            id: "v2",
            name: "v2"
          },
          position: {
            x: 170,
            y: 30
          },
          group: "nodes",
          removed: false,
          selected: false,
          selectable: false,
          locked: false,
          grabbable: false,
          classes: ""
        },
        {
          data: {
            id: "v3",
            name: "v3"
          },
          position: {
            x: 240,
            y: 30
          },
          group: "nodes",
          removed: false,
          selected: false,
          selectable: false,
          locked: false,
          grabbable: false,
          classes: ""
        },
        {
          data: {
            id: "v4",
            name: "v4"
          },
          position: {
            x: 310,
            y: 30
          },
          group: "nodes",
          removed: false,
          selected: false,
          selectable: false,
          locked: false,
          grabbable: false,
          classes: ""
        },
        {
          data: {
            id: "v5",
            name: "v5"
          },
          position: {
            x: 380,
            y: 30
          },
          group: "nodes",
          removed: false,
          selected: false,
          selectable: false,
          locked: false,
          grabbable: false,
          classes: ""
        },
        {
          data: {
            id: "v6",
            name: "v6"
          },
          position: {
            x: 450,
            y: 30
          },
          group: "nodes",
          removed: false,
          selected: false,
          selectable: false,
          locked: false,
          grabbable: false,
          classes: ""
        },
        {
          data: {
            id: "v7",
            name: "v7"
          },
          position: {
            x: 520,
            y: 30
          },
          group: "nodes",
          removed: false,
          selected: false,
          selectable: false,
          locked: false,
          grabbable: false,
          classes: ""
        },
        {
          data: {
            id: "v8",
            name: "v8"
          },
          position: {
            x: 590,
            y: 30
          },
          group: "nodes",
          removed: false,
          selected: false,
          selectable: false,
          locked: false,
          grabbable: false,
          classes: ""
        },
        {
          data: {
            id: "v9",
            name: "v9"
          },
          position: {
            x: 660,
            y: 30
          },
          group: "nodes",
          removed: false,
          selected: false,
          selectable: false,
          locked: false,
          grabbable: false,
          classes: ""
        },
        {
          data: {
            id: "hidden1",
            name: "c0"
          },
          /*position: {
            x: 100,
            y: 150
          },*/
          style: {
            visibility: "hidden",
            display: "none"
          },
          group: "nodes",
          removed: false,
          selected: false,
          selectable: false,
          locked: false,
          grabbable: false,
          classes: ""
        },
        {
          data: {
            id: "hidden2",
            name: "c0"
          },
          /*position: {
            x: 100,
            y: 150
          },*/
          style: {
            visibility: "hidden",
            display: "none"
          },
          group: "nodes",
          removed: false,
          selected: false,
          selectable: false,
          locked: false,
          grabbable: false,
          classes: ""
        },
        {
          data: {
            id: "c0",
            name: "c0"
          },
          position: {
            x: 100,
            y: 150
          },
          group: "nodes",
          removed: false,
          selected: false,
          selectable: false,
          locked: false,
          grabbable: false,
          classes: ""
        },
        {
          data: {
            id: "c1",
            name: "c1"
          },
          position: {
            x: 222,
            y: 150
          },
          group: "nodes",
          removed: false,
          selected: false,
          selectable: false,
          locked: false,
          grabbable: false,
          classes: ""
        },
        {
          data: {
            id: "c2",
            name: "c2"
          },
          position: {
            x: 344,
            y: 150
          },
          group: "nodes",
          removed: false,
          selected: false,
          selectable: false,
          locked: false,
          grabbable: false,
          classes: ""
        },
        {
          data: {
            id: "c3",
            name: "c3"
          },
          position: {
            x: 466,
            y: 150
          },
          group: "nodes",
          removed: false,
          selected: false,
          selectable: false,
          locked: false,
          grabbable: false,
          classes: ""
        },
        {
          data: {
            id: "c4",
            name: "c4"
          },
          position: {
            x: 588,
            y: 150
          },
          group: "nodes",
          removed: false,
          selected: false,
          selectable: false,
          locked: false,
          grabbable: false,
          classes: ""
        },
        {
          data: {
            id: "e0",
            source: "v0",
            target: "c0"
          },
          position: { },
          group: "edges",
          removed: false,
          selected: false,
          selectable: false,
          locked: false,
          grabbable: false,
          classes: ""
          },
          {
          data: {
            id: "e1",
            source: "v0",
            target: "c1"
          },
          position: { },
          group: "edges",
          removed: false,
          selected: false,
          selectable: false,
          locked: false,
          grabbable: false,
          classes: ""
          },
          {
          data: {
            id: "e2",
            source: "v1",
            target: "c0"
          },
          position: { },
          group: "edges",
          removed: false,
          selected: false,
          selectable: false,
          locked: false,
          grabbable: false,
          classes: ""
          },
          {
          data: {
            id: "e3",
            source: "v1",
            target: "c4"
          },
          position: { },
          group: "edges",
          removed: false,
          selected: false,
          selectable: false,
          locked: false,
          grabbable: false,
          classes: ""
          },
          {
          data: {
            id: "e4",
            source: "v2",
            target: "c0"
          },
          position: { },
          group: "edges",
          removed: false,
          selected: false,
          selectable: false,
          locked: false,
          grabbable: false,
          classes: ""
          },
          {
          data: {
            id: "e5",
            source: "v2",
            target: "c2"
          },
          position: { },
          group: "edges",
          removed: false,
          selected: false,
          selectable: false,
          locked: false,
          grabbable: false,
          classes: ""
          },
          {
          data: {
            id: "e6",
            source: "v3",
            target: "c3"
          },
          position: { },
          group: "edges",
          removed: false,
          selected: false,
          selectable: false,
          locked: false,
          grabbable: false,
          classes: ""
          },
          {
          data: {
            id: "e7",
            source: "v3",
            target: "c4"
          },
          position: { },
          group: "edges",
          removed: false,
          selected: false,
          selectable: false,
          locked: false,
          grabbable: false,
          classes: ""
          },
          {
          data: {
            id: "e8",
            source: "v4",
            target: "c1"
          },
          position: { },
          group: "edges",
          removed: false,
          selected: false,
          selectable: false,
          locked: false,
          grabbable: false,
          classes: ""
          },
          {
          data: {
            id: "e9",
            source: "v4",
            target: "c2"
          },
          position: { },
          group: "edges",
          removed: false,
          selected: false,
          selectable: false,
          locked: false,
          grabbable: false,
          classes: ""
          },
          {
          data: {
            id: "e10",
            source: "v5",
            target: "c0"
          },
          position: { },
          group: "edges",
          removed: false,
          selected: false,
          selectable: false,
          locked: false,
          grabbable: false,
          classes: ""
          },
          {
          data: {
            id: "e11",
            source: "v5",
            target: "c3"
          },
          position: { },
          group: "edges",
          removed: false,
          selected: false,
          selectable: false,
          locked: false,
          grabbable: false,
          classes: ""
          },
          {
          data: {
            id: "e12",
            source: "v6",
            target: "c2"
          },
          position: { },
          group: "edges",
          removed: false,
          selected: false,
          selectable: false,
          locked: false,
          grabbable: false,
          classes: ""
          },
          {
          data: {
            id: "e13",
            source: "v6",
            target: "c4"
          },
          position: { },
          group: "edges",
          removed: false,
          selected: false,
          selectable: false,
          locked: false,
          grabbable: false,
          classes: ""
          },
          {
          data: {
            id: "e14",
            source: "v7",
            target: "c1"
          },
          position: { },
          group: "edges",
          removed: false,
          selected: false,
          selectable: false,
          locked: false,
          grabbable: false,
          classes: ""
          },
          {
          data: {
            id: "e15",
            source: "v7",
            target: "c3"
          },
          position: { },
          group: "edges",
          removed: false,
          selected: false,
          selectable: false,
          locked: false,
          grabbable: false,
          classes: ""
          },
          {
          data: {
            id: "e16",
            source: "v8",
            target: "c1"
          },
          position: { },
          group: "edges",
          removed: false,
          selected: false,
          selectable: false,
          locked: false,
          grabbable: false,
          classes: ""
          },
          {
          data: {
            id: "e17",
            source: "v8",
            target: "c4"
          },
          position: { },
          group: "edges",
          removed: false,
          selected: false,
          selectable: false,
          locked: false,
          grabbable: false,
          classes: ""
          },
          {
          data: {
            id: "e18",
            source: "v9",
            target: "c2"
          },
          position: { },
          group: "edges",
          removed: false,
          selected: false,
          selectable: false,
          locked: false,
          grabbable: false,
          classes: ""
          },
          {
          data: {
            id: "e19",
            source: "v9",
            target: "c3"
          },
          position: { },
          group: "edges",
          removed: false,
          selected: false,
          selectable: false,
          locked: false,
          grabbable: false,
          classes: ""
          }/*,
        {
          data: {
            id: "v2"
          },
          position: {
            x: 2,
            y: 0
          },
          group: "nodes",
          removed: false,
          selected: false,
          selectable: false,
          locked: false,
          grabbable: false,
          classes: ""
        },
        {
          data: {
            id: "v3"
          },
          position: {
            x: 3,
            y: 0
          },
          group: "nodes",
          removed: false,
          selected: false,
          selectable: false,
          locked: false,
          grabbable: false,
          classes: ""
        },
        {
          data: {
            id: "v4"
          },
          position: {
            x: 4,
            y: 0
          },
          group: "nodes",
          removed: false,
          selected: false,
          selectable: false,
          locked: false,
          grabbable: false,
          classes: ""
        },
        {
          data: {
            id: "c1"
          },
          position: {
            x: 0,
            y: 1
          },
          group: "nodes",
          removed: false,
          selected: false,
          selectable: false,
          locked: false,
          grabbable: false,
          classes: ""
        },
        {
          data: {
            id: "c2"
          },
          position: {
            x: 1,
            y: 1
          },
          group: "nodes",
          removed: false,
          selected: false,
          selectable: false,
          locked: false,
          grabbable: false,
          classes: ""
        },
        {
          data: {
            id: "c3"
          },
          position: {
            x: 2,
            y: 1
          },
          group: "nodes",
          removed: false,
          selected: false,
          selectable: false,
          locked: false,
          grabbable: false,
          classes: ""
        }*/

      ]
    });
});