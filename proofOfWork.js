var robotjs = require('./build/Release/robotjs.node');

// 3 seconds to open notepad and let robot write some text
setTimeout(() => {
    robotjs.typeString("executing robotjs.typeStringDelayed(\"Olá € `.´\", 500): ");
    robotjs.typeStringDelayed("Olá € `.´", 500);
}, 3000);