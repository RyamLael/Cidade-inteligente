let socket = null;

const connectionStatus =
    document.getElementById(
        "connectionStatus"
    );

const temperature =
    document.getElementById(
        "temperature"
    );

const humidity =
    document.getElementById(
        "humidity"
    );

const ambientLight =
    document.getElementById(
        "ambientLight"
    );

const gateLight =
    document.getElementById(
        "gateLight"
    );

const gateState =
    document.getElementById(
        "gateState"
    );

const jsonViewer =
    document.getElementById(
        "jsonViewer"
    );

const cityInput =
    document.getElementById(
        "cityInput"
    );

function connectWebSocket()
{
    socket =
        new WebSocket(
            `ws://${window.location.host}/ws`
        );

    socket.onopen =
        () =>
    {
        connectionStatus.textContent =
            "Conectado";
    };

    socket.onclose =
        () =>
    {
        connectionStatus.textContent =
            "Desconectado";

        setTimeout(
            connectWebSocket,
            2000
        );
    };

    socket.onerror =
        () =>
    {
        connectionStatus.textContent =
            "Erro";
    };

    socket.onmessage =
        (event) =>
    {
        const data =
            JSON.parse(
                event.data
            );

        temperature.textContent =
            data.temperature;

        humidity.textContent =
            data.humidity;

        ambientLight.textContent =
            data.ambientLight;

        gateLight.textContent =
            data.gateLight;

        gateState.textContent =
            data.gateOpen
                ? "Aberta"
                : "Fechada";

        jsonViewer.textContent =
            JSON.stringify(
                data,
                null,
                2
            );
    };
}

document
    .getElementById(
        "cityButton"
    )
    .addEventListener(
        "click",
        () =>
        {
            if (
                !socket ||
                socket.readyState !== WebSocket.OPEN
            )
            {
                return;
            }

            socket.send(
                JSON.stringify({
                    command:
                        "set_city",

                    city:
                        cityInput.value
                })
            );
        }
    );

document
    .getElementById(
        "openGateButton"
    )
    .addEventListener(
        "click",
        () =>
        {
            socket.send(
                JSON.stringify({
                    command:
                        "open_gate"
                })
            );
        }
    );

document
    .getElementById(
        "closeGateButton"
    )
    .addEventListener(
        "click",
        () =>
        {
            socket.send(
                JSON.stringify({
                    command:
                        "close_gate"
                })
            );
        }
    );

connectWebSocket();