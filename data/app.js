document.addEventListener('DOMContentLoaded', () => {

    const cards = document.querySelectorAll('.card');
    const cityCard = cards[0];
    const lightCard = cards[1];
    const gateCard = cards[2];

    // 1. Abrir e Fechar as Drawers (Cards)
    cards.forEach(card => {
        const header = card.querySelector('.card-header');
        const body = card.querySelector('.card-body');
        const chevron = card.querySelector('.chevron-icon');

        if (header && body) {
            header.style.cursor = 'pointer';

            header.addEventListener('click', () => {
                const isVisible = window.getComputedStyle(body).display !== 'none';

                if (isVisible) {
                    body.style.display = 'none';
                    if (chevron) chevron.style.transform = 'rotate(180deg)';
                } else {
                    body.style.display = 'flex';
                    if (chevron) chevron.style.transform = 'rotate(0deg)';
                }
            });
        }
    });

    // 2. Atualiza o nome da cidade
    const pageTitle = document.querySelector('.page-title');
    const cityInput = cityCard ? cityCard.querySelector('#city-input') : null;
    const saveCityBtn = cityCard ? cityCard.querySelector('.btn') : null;

    const citySubtitle = document.createElement('p');
    citySubtitle.className = 'city-subtitle';
    citySubtitle.style.fontSize = '0.9rem';
    citySubtitle.style.color = '#64748b';
    citySubtitle.style.marginTop = '4px';
    pageTitle.after(citySubtitle);

    if (saveCityBtn && cityInput) {
        saveCityBtn.addEventListener('click', () => {
            const cityVal = cityInput.value.trim();
            if (cityVal !== '') {
                citySubtitle.textContent = `Nome da cidade: ${cityVal}`;
            }
        });
    }

    // 3. Iluminação
    if (lightCard) {
        const lightBtn = lightCard.querySelector('.btn');
        const lightStatusBox = lightCard.querySelector('.status-box');
        const lampCircle = lightCard.querySelector('.lamp-circle');
        const lampIcon = lampCircle ? lampCircle.querySelector('svg') : null; // Captura o ícone SVG
        const lightText = lightStatusBox ? lightStatusBox.querySelector('span') : null;

        let isLightOn = true;

        if (lightBtn && lightStatusBox && lampCircle && lightText) {
            lightBtn.addEventListener('click', () => {
                isLightOn = !isLightOn;

                if (!isLightOn) {
                    // Desligar luzes
                    lightStatusBox.style.borderColor = '#0D193A';
                    lampCircle.style.backgroundColor = '#0D193A';
                    if (lampIcon) lampIcon.style.stroke = '#FFFFFF'; // Torna o ícone branco

                    lightText.textContent = 'Luzes Desligadas';
                    lightBtn.textContent = 'Ligar';
                    lightBtn.classList.remove('btn-red');
                    lightBtn.classList.add('btn-green');
                } else {
                    // Acender luzes
                    lightStatusBox.style.borderColor = '#eab308';
                    lampCircle.style.backgroundColor = '#eab308';
                    if (lampIcon) lampIcon.style.stroke = '#121a30'; // Volta à cor original do SVG

                    lightText.textContent = 'Luzes Ligadas';
                    lightBtn.textContent = 'Desligar';
                    lightBtn.classList.remove('btn-green');
                    lightBtn.classList.add('btn-red');
                }
            });
        }
    }

    // 4. Cancela
    if (gateCard) {
        const gateBtn = gateCard.querySelector('.btn');
        const gateStatusBox = gateCard.querySelector('.status-box');
        const gateDot = gateCard.querySelector('.status-dot-green');
        const gateText = gateStatusBox ? gateStatusBox.querySelector('span:last-child') : null;

        let isGateOpen = true;

        if (gateBtn && gateStatusBox && gateDot && gateText) {
            gateBtn.addEventListener('click', () => {
                isGateOpen = !isGateOpen;

                if (!isGateOpen) {
                    // Fecha a cancela
                    gateStatusBox.style.borderColor = '#852222';
                    gateDot.style.backgroundColor = '#852222';
                    gateText.textContent = 'Fechada';
                    gateBtn.textContent = 'Ligar'; // Conforme o requisito 4c ("Ligar")
                    gateBtn.classList.remove('btn-red');
                    gateBtn.classList.add('btn-green');
                } else {
                    // Abre a cancela
                    gateStatusBox.style.borderColor = '#22c55e';
                    gateDot.style.backgroundColor = '#22c55e';
                    gateText.textContent = 'Aberta';
                    gateBtn.textContent = 'Fechar';
                    gateBtn.classList.remove('btn-green');
                    gateBtn.classList.add('btn-red');
                }
            });
        }
    }

});
