import QtQuick

import "qml/components/"

Window {
    width: 640
    height: 480
    visible: true
    title: qsTr("Hello World")

    ListView {
        id: itensListView
        anchors.fill: parent
        anchors.topMargin: 10
        anchors.bottomMargin: 10
        spacing: 10
        model: 10
        delegate: Card{ contentChildren: ItemVolumeController {} }
    }
}
