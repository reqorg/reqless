# reqless
A Node.js HTTP client written in C++, with focus on performance, reliability and safety.

## Installation

Using npm:

https://www.npmjs.com/package/reqless

```bash
$ npm install reqless
```

## Usage
```js
const reqless = require("reqless")

const response = reqless({ 
    url: "http://info.cern.ch/",
    method: "GET"
})
console.log(response.body, response.headers);
```

## Response
The main reqless function returns a `response` object.
A response object has the following attributes:
  - body: The body received from the HTTP request (string).
  - headers: The headers received from the HTTP request (object).

## Request
Inside the request object you can provide the following attributes:
  - url: The url which will be requested (string).
  - method: The method in which the url will be requested, default - GET (string).
  - data: POST data for the request (string).
