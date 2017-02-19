<?php
echo "here ";

include 'wa_wrapper/WolframAlphaEngine.php';
$engine = new WolframAlphaEngine( 'QVH4Q7-W8QGGVT8H2' );

$resp = $engine->getResults("pi");

$pod = $resp->getPods();

$pod = $pod[1];

foreach($pod->getSubpods() as $subpod){
  if($subpod->plaintext){
    $plaintext = $subpod->plaintext;
    // break;
  }
}

$result = substr($plaintext, 0,strlen($plaintext)-3);

echo $plaintext;
?>
