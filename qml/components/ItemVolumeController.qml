import QtQuick 2.0
import QtQuick.Layouts 1.3
import QtQuick.Controls
import QtQuick.Controls.Material 2.12
import QtQuick.Controls.Material.impl 2.12

ColumnLayout {
    property string itemName: ""

    anchors.fill: parent
    RowLayout {
        id: cardRow

        Text {
            text: itemName
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
