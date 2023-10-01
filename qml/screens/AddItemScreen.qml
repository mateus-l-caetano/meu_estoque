import QtQuick
import QtQuick.Layouts 1.3
import QtQuick.Controls
import QtQuick.Controls.Material 2.3
import QtQuick.Controls.Material.impl 2.3

import "../components/"

ColumnLayout {
    id: container
    Item { Layout.fillHeight: true }

    Column {
        Layout.alignment: Qt.AlignHCenter
        padding: 16
        bottomPadding: 0
        Label {
            text: "Nome"
            font.weight: Font.Bold
        }

        TextField {
            width: container.width - 32
        }
    }

    Row {
        Layout.fillWidth: true
        Column {
            padding: 16
            topPadding: 8
            Label {
                text: "Categoria"
                font.weight: Font.Bold
            }

            ComboBox {
                model: ["Categoria 1", "Categoria 2", "Categoria 3", "Categoria 4", "Categoria 5"]
                width: 150
            }
        }

        Column {
            padding: 16
            topPadding: 8
            Label {
                text: "Preço"
                font.weight: Font.Bold
                bottomPadding: 4
            }

            SpinBox {
                property int decimals: 2
                property real realValue: 0.0
                property real realFrom: 0.0
                property real realTo: 10000.0
                property real realStepSize: 1.0
                property real factor: Math.pow(10, decimals)

                id: spinbox
                editable: true
                stepSize: realStepSize * factor
                value: realValue * factor
                to : realTo * factor
                from : realFrom * factor
                validator: DoubleValidator {
                    bottom: Math.min(spinbox.from, spinbox.to)*spinbox.factor
                    top:  Math.max(spinbox.from, spinbox.to)*spinbox.factor
                    notation: DoubleValidator.StandardNotation
                    decimals: 2
                }

                textFromValue: function(value, locale) {
                    return parseFloat(value*1.0/factor).toFixed(decimals);
                }

                inputMethodHints: Qt.ImhFormattedNumbersOnly
            }
        }

        Column {
            padding: 16
            topPadding: 8
            Label {
                text: "Quantidade"
                font.weight: Font.Bold
                bottomPadding: 4
            }

            SpinBox { value: 0 }
        }
    }

    Row {
        Layout.alignment: Qt.AlignHCenter
        spacing: 16
        Button {
            text: "salvar"
            highlighted: true
        }
        Button {
            text: "cancelar"
        }
    }

    Item { Layout.fillHeight: true }
}
