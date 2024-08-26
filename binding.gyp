{
  "targets": [
    {
      "target_name": "reqless",
      "cflags!": [ "-fno-exceptions", "-g" ],
      "cflags_cc!": [ "-fno-exceptions", "-lssl", "-lcrypto", "-g" ],
      "sources": [ "reqless.cc" ],
      "include_dirs": [
        "<!@(node -p \"require('node-addon-api').include\")"
      ],
      'defines': [ 'NAPI_DISABLE_CPP_EXCEPTIONS' ],
    }
  ]
}
