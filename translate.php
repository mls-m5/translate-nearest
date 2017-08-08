<?php

// ini_set('display_errors', 1);
// ini_set('display_startup_errors', 1);
// error_reporting(E_ALL);


//http://stackoverflow.com/questions/900207/return-a-php-page-as-an-image
// header("Content-Type: image/png");
// header("Content-Length: " . filesize($name));

$descriptorspec = array(
   0 => array("pipe", "r"),  // stdin is a pipe that the child will read from
   1 => array("pipe", "w"),  // stdout is a pipe that the child will write to
   2 => array("file", "/dev/null", "a") // stderr is a file to write to
);

//http://php.net/manual/en/function.proc-open.php
$cwd = NULL; // '/tmp'; Absolute path or null if the same as the current php process
$env = array('some_option' => 'aeiou');

$density = 77;
if (!empty($_GET["density"])) {
    $density = $_GET["density"];
}

$script = "./translate";

$process = proc_open($script, $descriptorspec, $pipes, $cwd, $env);
// $process = proc_open('./script.sh', $descriptorspec, $pipes);

if (is_resource($process)) {
    // $pipes now looks like this:
    // 0 => writeable handle connected to child stdin
    // 1 => readable handle connected to child stdout
    // Any error output will be appended to /tmp/error-output.txt

    $melody = $_GET["text"];

    if (!$melody) {
        $melody = "hej";
    }

    fwrite($pipes[0], $melody);
    fclose($pipes[0]);

    fpassthru($pipes[1]);
    // echo stream_get_contents($pipes[1]);
    fclose($pipes[1]);

    // It is important that you close any pipes before calling
    // proc_close in order to avoid a deadlock
    $return_value = proc_close($process);
}

exit;

//no trailing space to make sure there is no whitespace added