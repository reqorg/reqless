const reqless = require('bindings')('reqless');
log = console.log

const response = reqless.req("http://info.cern.ch/", "GET")
log("BODY")
log(response.body)
log("HEADERS")
log(response.headers)
