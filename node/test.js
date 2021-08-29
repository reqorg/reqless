const reqless = require('bindings')('reqless');
log = console.log

const response = reqless.req("http://info.cern.ch/", "GET")
log(response)
