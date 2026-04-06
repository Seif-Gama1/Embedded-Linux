import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import QtCore

Window {
    id: root
    width: 1024 // Increased width to better fit the dashboard design
    height: 600
    visible: true
    title: qsTr("Weatherly")
    color: "#222"

    // --- Background Layer ---
    Image {
        id: backgroundImage
        anchors.fill: parent
        source: "background.jpg"
        fillMode: Image.PreserveAspectCrop

        Rectangle {
            anchors.fill: parent
            color: "black"
            opacity: 0.3
        }
    }

    // --- Top Left: Main Weather Info ---
    Column {
        anchors { top: parent.top; left: parent.left; margins: 40 }
        spacing: 5

        Image {
            id: conditionIcon
            source: "fog.png"
            width: 80; height: 80
        }

        Text {
            id: conditionLabel
            text: "---"
            color: "white"
            font.pixelSize: 32
            font.bold: true
        }

        Text {
            id: locationLabel
            text: "Loading..."
            color: "white"
            font.pixelSize: 18
            opacity: 0.8
        }

        Text {
            id: mainTemp
            text: "-- °C"
            color: "white"
            font.pixelSize: 72
            font.bold: true
        }

        Button {
            text: "📍 Change Location"
            flat: true
            contentItem: Text {
                text: parent.text
                color: "white"
                font.pixelSize: 14
                font.underline: true
            }
            onClicked: locationDialog.open()
        }
    }

    // --- Top Right: Extra Details ---
    ColumnLayout {
        anchors { top: parent.top; right: parent.right; margins: 50 }
        spacing: 25

        WeatherDetailItem {
            id: humidityItem
            labelText: "Humidity"
            iconSource: "humidity.png"
        }

        WeatherDetailItem {
            id: pressureItem
            labelText: "Air Pressure"
            iconSource: "air.png"
        }

        WeatherDetailItem {
            id: rainItem
            labelText: "Chance of Rain"
            iconSource: "heavy-rain.png"
        }

        WeatherDetailItem {
            id: windItem
            labelText: "Wind Speed"
            iconSource: "windy.png"
        }
    }

    // --- Bottom: Hourly Forecast ---
    Item {
        width: parent.width * 0.85
        height: 200
        anchors { bottom: parent.bottom; horizontalCenter: parent.horizontalCenter; margins: 30 }

        Row {
            anchors { top: parent.top; right: parent.right; rightMargin: 10 }
            spacing: 20
            z: 2 // Ensure arrows are above the list

            Text {
                text: "＜"
                color: "white"; font.pixelSize: 24
                MouseArea { anchors.fill: parent; onClicked: forecastView.decrementCurrentIndex() }
            }
            Text {
                text: "＞"
                color: "white"; font.pixelSize: 24
                MouseArea { anchors.fill: parent; onClicked: forecastView.incrementCurrentIndex() }
            }
        }

        ListView {
            id: forecastView
            anchors.fill: parent
            anchors.topMargin: 40
            orientation: ListView.Horizontal
            spacing: 15
            model: forecastModel
            clip: true

            // Animation & Snapping
            highlightMoveDuration: 300
            snapMode: ListView.SnapToItem

            delegate: HourlyForecastDelegate {
                time: model.time
                temp: model.temp
                feelsLike: model.feelsLike
                isCurrent: index === forecastView.currentIndex
            }
        }
    }

    ListModel { id: forecastModel }

    // --- Dialog for Changing Location ---
    Dialog {
        id: locationDialog
        title: "Enter City Name"
        standardButtons: Dialog.Ok | Dialog.Cancel
        anchors.centerIn: parent

        TextField {
            id: cityInput
            placeholderText: "e.g. London, Tokyo..."
            width: parent.width
            onAccepted: locationDialog.accept()
        }

        onAccepted: {
            updateWeather(cityInput.text)
            cityInput.clear()
        }
    }

    // --- Logic Section ---

    function fetchData(url, callback) {
        var xhr = new XMLHttpRequest()
        xhr.onreadystatechange = function() {
            if (xhr.readyState === XMLHttpRequest.DONE) {
                if (xhr.status === 200) {
                    callback(JSON.parse(xhr.responseText))
                } else {
                    console.log("Network Error: " + xhr.status)
                    callback(null)
                }
            }
        }
        xhr.open("GET", url)
        xhr.send()
    }

    function updateWeather(targetCity) {
        var apiKey = "8ca0c7374f4e4d6aadd191556260103";
        var url = "https://api.weatherapi.com/v1/forecast.json?key=" + apiKey + "&q=" + targetCity + "&days=1&aqi=no";

        fetchData(url, function(data) {
            if (!data) return;

            // 1. Update Main Center Stats
            mainTemp.text = Math.round(data.current.temp_c) + " °C";
            conditionLabel.text = data.current.condition.text;
            locationLabel.text = data.location.name + ", " + data.location.country;
            conditionIcon.source = "https:" + data.current.condition.icon

            // 2. Update Right Side Details
            humidityItem.valueText = data.current.humidity + " %";
            pressureItem.valueText = data.current.pressure_mb + " hPa";

            var localTime = new Date(data.location.localtime.replace(" ", "T"));
            var currentHour = localTime.getHours();

            // var hourData = data.forecast.forecastday[0].hour[currentHour];

            // rainItem.valueText = data.forecast.forecastday[0].day.daily_chance_of_rain + " %";
            rainItem.valueText = "20 %"


            windItem.valueText = data.current.wind_kph + " km/h";

            // 3. Update Hourly Model
            forecastModel.clear();
            var hoursArray = data.forecast.forecastday[0].hour;

            hoursArray.forEach(function(hourData) {
                forecastModel.append({
                    "time": formatTime(hourData.time),
                    "temp": Math.round(hourData.temp_c) + "°C",
                    "feelsLike": Math.round(hourData.feelslike_c) + "°C"
                });
            });

            // Auto-scroll to current hour
            forecastView.currentIndex = currentHour;
        });
    }

    function formatTime(rawTime) {
        var date = new Date(rawTime.replace(/-/g, "/"));
        var hours = date.getHours();
        var ampm = hours >= 12 ? 'PM' : 'AM';
        hours = hours % 12;
        hours = hours ? hours : 12;
        return hours + ' ' + ampm;
    }

    Component.onCompleted: updateWeather("Cairo")
}
