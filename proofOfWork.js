var robotjs = require('./build/Release/robotjs.node');

setTimeout(() => {
    robotjs.typeStringDelayed("Olá € `.´", 1500);
}, 3000);