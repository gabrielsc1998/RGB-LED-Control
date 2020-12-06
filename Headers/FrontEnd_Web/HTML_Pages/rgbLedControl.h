// ********************************************************************************************
//                         ENSA Tecnologia - Projeto: ENSA MED-200S                               
// --------------------------------------------------------------------------------------------
//
// Arquivo: rgbLedControl.h
//
// Autor  : Gabriel da Silva Caetano <98gabrielSc@gmail.com>
// Autor  : Jânio Anselmo <janio@ensa.com.br>
//
// ********************************************************************************************

// ----------------------------------------------------------------------------------------- //

#ifndef _RGB_LED_CONTROL_H
#define _RGB_LED_CONTROL_H

// ----------------------------------------------------------------------------------------- //

const char htmlPageRGBLedControl[] PROGMEM = R"rawliteral(
  <head>
    <title>Data e Hora</title>
    <meta name='viewport' content='width=device-width, initial-scale=1' charset='UTF-8'>
    <style>
      html {
        font-family: Calibri; 
        margin: 0; padding: 0;
      }
      .centralize {
        left: 50%; top: 50%; 
        transform: translate(-50%, -50%);
      }
      .centerItens {
        justify-content: center;
        align-items: center;
        text-align: center;
      }
      .aling {
        flex: 1; display: flex;
        flex-direction: column;
      }
      .mainContainer { 
        position: absolute;
        border-radius: 4px;
        box-shadow: 0 0 6px #015356; 
        width: 98%; height: 98%;
        max-width: 850px;
        max-height: 850px;
        overflow: scroll;
      }
      button {
        outline: none;
        cursor: pointer; 
        color: white; 
        border: none;
        border-radius: 6px;
        background-color: #26A69A;
        box-shadow: 0 0 1.5px #015356; 
      }
      button:hover { filter: brightness(95%); }
      input {
        width: 85%;
      }
      .buttonLed {
        width: 100%;
        max-width: 150px; 
        height: 30px;
        font-size: 14px;
        margin-top: 50px;
      }
      .divResponsive {
        width: 100%;
      }
      @media (max-height: 640px) {
      @media (max-height: 400px) {
        .aling {
          justify-content: flex-start;
        }
      }
    </style>
    <script type='text/javascript'>
      const dataLed = {
        status: 0,
        R: 0,
        G: 0,
        B: 0
      };

      function getById(id) {
        return document.getElementById(id);
      }

      function changeRange(range) {
          
        if(range === 'R') {
          dataLed.R = parseInt(getById('rangeR').value);
        } else if(range === 'G') {
          dataLed.G = parseInt(getById('rangeG').value);
        } else if(range === 'B') {
          dataLed.B = parseInt(getById('rangeB').value);
        } 

        sendDataLed();
      }
      
      function initPage() {
        getById('rangeR').addEventListener('change', function(){changeRange('R')}, false);
        getById('rangeG').addEventListener('change', function(){changeRange('G')}, false);
        getById('rangeB').addEventListener('change', function(){changeRange('B')}, false);
        getDataLed();
        setInterval(() => { getDataLed(); }, 1000);
      }

      function getDataLed() {
        const req = new XMLHttpRequest();
        req.open('GET', '/getDataLed', false );
        // req.open('GET', 'http://localhost:3000/getDataLed', false )
        req.send();
        if (req.status === 200) {
          const data = JSON.parse(req.responseText);
          dataLed.status = data.status;
          dataLed.R = data.R;
          dataLed.G = data.G;
          dataLed.B = data.B;
          getById('rangeR').value = dataLed.R;
          getById('rangeG').value = dataLed.G;
          getById('rangeB').value = dataLed.B;

          const buttonLed = document.getElementById('buttonLed');
          if(!dataLed.status) {
            buttonLed.innerHTML = 'LED - TURN ON';
            buttonLed.style.backgroundColor = '#FF1616';
          } else {
            buttonLed.innerHTML = 'LED - TURN OFF';
            buttonLed.style.backgroundColor = '#53BD38';
          }
        } else {
          alert("Nenhum dado recebido");
        }
      }

      function changeLedStatus() {
        dataLed.status === 0 ? dataLed.status = 1 : dataLed.status = 0;
        sendDataLed(); getDataLed();
      }

      function sendDataLed() {
        const req = new XMLHttpRequest();
        req.open('POST', '/setDataLed', false);
        // req.open('POST', 'http://localhost:3000/setDataLed', false);
        req.setRequestHeader("Content-type", "application/json");
        req.send(JSON.stringify(dataLed));
        getDataLed();
      }
    </script>
  </head>
  <body onload='initPage()'>
    <div class='centralize centerItens aling mainContainer'>
      <div class='divResponsive centerItens'>
        <div class='divResponsive'> Controle: R </div>
        <div class='divResponsive'>
          <input type='range' min='0' max='255' step='1' id='rangeR'>
        </div>
        <div class='divResponsive'> Controle: G </div>
        <div class='divResponsive'>
          <input type='range' min='0' max='255' step='1' id='rangeG'>
        </div>
        <div class='divResponsive'> Controle: B </div>
        <div class='divResponsive'>
          <input type='range' min='0' max='255' step='1' id='rangeB'>
        </div>
        <div class='divButton'>
          <button class='buttonLed' id='buttonLed' onclick='changeLedStatus()'> </button>
        </div>
      </div>
    </div>
  </body>
)rawliteral";

// ----------------------------------------------------------------------------------------- //

#endif

// ----------------------------------------------------------------------------------------- //

