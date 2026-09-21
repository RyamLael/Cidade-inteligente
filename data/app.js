let socket = null;

let cityInput;
let saveCityBtn;

let gateBtn;
let gateStatusBox;
let gateDot;
let gateText;

let lightBtn;

function connectWebSocket()
{
    socket =
        new WebSocket(
            `ws://${window.location.host}/ws`
        );

    socket.onopen =
        () =>
    {
        console.log(
            "WebSocket conectado"
        );

        requestState();
    };

    socket.onclose =
        () =>
    {
        console.log(
            "WebSocket desconectado"
        );

        setTimeout(
            connectWebSocket,
            2000
        );
    };

    socket.onerror =
        (error) =>
    {
        console.error(
            error
        );
    };

    socket.onmessage =
        (event) =>
    {
        const data =
            JSON.parse(
                event.data
            );

        console.log(
            "Estado recebido:",
            data
        );

        updateUI(
            data
        );
    };
}

function sendCommand(
    payload
)
{
    if (
        !socket ||
        socket.readyState !==
            WebSocket.OPEN
    )
    {
        console.warn(
            "WebSocket não conectado"
        );

        return;
    }

    socket.send(
        JSON.stringify(
            payload
        )
    );
}

function requestState()
{
    sendCommand({
        command:
            "request_state"
    });
}

function updateUI(
    data
)
{
    updateCity(
        data
    );

    updateGate(
        data
    );

    updateLighting(
        data
    );

    updateSensors(
        data
    );
}

function updateCity(
    data
)
{
    const subtitle =
        document.getElementById(
            "citySubtitle"
        );

    if (
        subtitle &&
        data.cityName
    )
    {
        subtitle.textContent =
            `Cidade: ${data.cityName}`;
    }

    if (
        cityInput &&
        document.activeElement !==
            cityInput
    )
    {
        cityInput.value =
            data.cityName ||
            "";
    }
}

function updateGate(
    data
)
{
    if (
        !gateBtn ||
        !gateStatusBox ||
        !gateDot ||
        !gateText
    )
    {
        return;
    }

    if (data.gateOpen)
    {
        gateStatusBox.style.borderColor =
            "#22c55e";

        gateDot.style.backgroundColor =
            "#22c55e";

        gateText.textContent =
            "Aberta";

        gateBtn.textContent =
            "Fechar";

        gateBtn.classList.remove(
            "btn-green"
        );

        gateBtn.classList.add(
            "btn-red"
        );
    }
    else
    {
        gateStatusBox.style.borderColor =
            "#852222";

        gateDot.style.backgroundColor =
            "#852222";

        gateText.textContent =
            "Fechada";

        gateBtn.textContent =
            "Abrir";

        gateBtn.classList.remove(
            "btn-red"
        );

        gateBtn.classList.add(
            "btn-green"
        );
    }
}

function updateLighting(
    data
)
{
    if (!lightBtn)
    {
        return;
    }

    if (
        data.streetLightBrightness >
        0
    )
    {
        lightBtn.textContent =
            "Desligar";
    }
    else
    {
        lightBtn.textContent =
            "Ligar";
    }
}

function updateSensors(
    data
)
{
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

    if (temperature)
    {
        temperature.textContent =
            data.temperature ??
            "--";
    }

    if (humidity)
    {
        humidity.textContent =
            data.humidity ??
            "--";
    }

    if (ambientLight)
    {
        ambientLight.textContent =
            data.ambientLight ??
            "--";
    }

    if (gateLight)
    {
        gateLight.textContent =
            data.gateLight ??
            "--";
    }
}

document.addEventListener(
    "DOMContentLoaded",
    () =>
    {
        const cards =
            document.querySelectorAll(
                ".card"
            );

        cards.forEach(
            (card) =>
            {
                const header =
                    card.querySelector(
                        ".card-header"
                    );

                const body =
                    card.querySelector(
                        ".card-body"
                    );

                const chevron =
                    card.querySelector(
                        ".chevron-icon"
                    );

                if (
                    !header ||
                    !body
                )
                {
                    return;
                }

                header.style.cursor =
                    "pointer";

                header.addEventListener(
                    "click",
                    () =>
                    {
                        const visible =
                            window
                                .getComputedStyle(
                                    body
                                )
                                .display !==
                            "none";

                        if (
                            visible
                        )
                        {
                            body.style.display =
                                "none";

                            if (
                                chevron
                            )
                            {
                                chevron.style.transform =
                                    "rotate(180deg)";
                            }
                        }
                        else
                        {
                            body.style.display =
                                "flex";

                            if (
                                chevron
                            )
                            {
                                chevron.style.transform =
                                    "rotate(0deg)";
                            }
                        }
                    }
                );
            }
        );

        cityInput =
            document.getElementById(
                "cityInput"
            );

        saveCityBtn =
            document.getElementById(
                "saveCityButton"
            );

        const pageTitle =
            document.querySelector(
                ".page-title"
            );

        const subtitle =
            document.createElement(
                "p"
            );

        subtitle.id =
            "citySubtitle";

        subtitle.className =
            "city-subtitle";

        subtitle.textContent =
            "Cidade: ---";

        pageTitle.after(
            subtitle
        );

        const gateCard =
            cards[2];

        gateBtn =
            gateCard.querySelector(
                ".btn"
            );

        gateStatusBox =
            gateCard.querySelector(
                ".status-box"
            );

        gateDot =
            gateCard.querySelector(
                ".status-dot-green"
            );

        gateText =
            gateStatusBox.querySelector(
                "span:last-child"
            );

        const lightCard =
            cards[1];

        lightBtn =
            lightCard.querySelector(
                ".btn"
            );

        if (saveCityBtn)
        {
            saveCityBtn.addEventListener(
                "click",
                () =>
                {
                    const city =
                        cityInput.value
                            .trim();

                    if (
                        city.length ===
                        0
                    )
                    {
                        return;
                    }

                    console.log(
                        "Cidade enviada:",
                        city
                    );

                    sendCommand({
                        command:
                            "set_city",

                        city:
                            city
                    });
                }
            );
        }

        if (gateBtn)
        {
            gateBtn.addEventListener(
                "click",
                () =>
                {
                    if (
                        gateText.textContent ===
                        "Aberta"
                    )
                    {
                        sendCommand({
                            command:
                                "close_gate"
                        });
                    }
                    else
                    {
                        sendCommand({
                            command:
                                "open_gate"
                        });
                    }
                }
            );
        }

        connectWebSocket();
    }
);