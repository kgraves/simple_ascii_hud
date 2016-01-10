Pebble.addEventListener('ready', function(e) {
  var req = new XMLHttpRequest();
  var url = 'http://api.wunderground.com/api/8b8f5f91e32d2fb1/conditions/q/CA/murrieta.json';

  req.open('GET', url, true);
  req.onload = function(e) {
    // readyState == 4 - DONE
    // https://developer.mozilla.org/en-US/docs/Web/API/XMLHttpRequest/readyState
    if (req.readyState == 4) {
      // status == 200 - HTTP OK
      if(req.status == 200) {
        var response = JSON.parse(req.responseText);

        Pebble.sendAppMessage({
            'temperature': response.current_observation.temp_f.toString(),
            'conditions': response.current_observation.weather,
        }, function sendAppMessageSuccess(e) {
          console.log('message send success');
        }, function sendAppMessageFailure() {
          // TODO notify about failure
          console.log('message send failed');
        });
      } else {
        // TODO notify about http failure
        console.log('Request returned error code ' + req.status.toString());
      }
    }
  };
  req.send(null);
});
