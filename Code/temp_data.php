
<!doctype html>
<html lang="fr">
<head>
  <meta charset="utf-8">
  <title>TP ESP8266</title>
  <link rel="stylesheet" href="style.css">
</head>
<body>
    <?php
        $temp = $_GET["temp"];
        $date = date("Y-m-d H:i:s");
        $file = 'temperature.txt';
        $current = file_get_contents($file);
        $current .= $date . " - Température : " . $temp . "°C\n";
        file_put_contents($file, $current);
    ?>
</body>
</html>