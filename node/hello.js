var addon = require('bindings')('hello');

console.log(addon.req("https://aaa.com", "GET"));
