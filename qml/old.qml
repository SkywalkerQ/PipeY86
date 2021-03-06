import QtQuick 2.0
import QtGraphicalEffects 1.0

Item {
    width: 320;
    height: 240;

    Item {
        id: container;
        anchors.centerIn: parent;
        width:  rect.width  + (2 * rectShadow.radius);
        height: rect.height + (2 * rectShadow.radius);

        Rectangle {
            id: rect
            width: 100;
            height: 50;
            color: "lightblue";
            radius: 0;
            antialiasing: true;
            anchors.centerIn: parent;
        }
    }
    DropShadow {
        id: rectShadow;
        anchors.fill: source
        cached: true;
        horizontalOffset: 3;
        verticalOffset: 3;
        radius: 8.0;
        samples: 16;
        color: "#80000000";
        smooth: true;
        source: container;
    }
}
