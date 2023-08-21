import QtQuick 2.0
import QtQuick.Controls
import QtQuick.Layouts 1.3
import QtQuick.Controls.Material 2.12
import QtQuick.Controls.Material.impl 2.12

Pane {
    id: cardRoot
    width: parent.width * 0.8
    anchors.horizontalCenter: parent.horizontalCenter

    background: Rectangle {
        radius: 10

        layer.enabled: true
        layer.effect: ElevationEffect {
            elevation: 1
        }
    }

    contentChildren: ColumnLayout {
        anchors.fill: parent
        RowLayout {
            id: cardRow

            Text {
                id: itemName
                text: qsTr("nome do item")
                Layout.fillWidth: true
                verticalAlignment: Qt.AlignVCenter
            }

            Row {
                Layout.alignment: Qt.AlignRight
                spacing: 8
                RoundButton {
                    text: "-"
                }
                TextInput {
                    text: "56"
                    anchors.verticalCenter: parent.verticalCenter
                }
                RoundButton {
                    text: "+"
                }
            }
        }
    }

}
