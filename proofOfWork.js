var robotjs = require('./build/Release/robotjs.node');

setTimeout(() => {
    robotjs.typeStringDelayed("Olá € `.´", 470);
}, 3000);