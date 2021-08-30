const reqless = require("./index")
const fetch = require('node-fetch');

const r1 = Date.now();

for (let index = 0; index < 1; index++) {
    //fetch('http://info.cern.ch/').then(res => res.text())
   // .then(body => console.log(body));
   reqless({
    url:'http://info.cern.ch/',
    method: "GET"
    })
}
const r2 = Date.now();
console.log(r2-r1);
