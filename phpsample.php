<?php
/*
 command: php -S 0.0.0.0:80 phpsample.php 
 will let server listener in port 80
 so we do simple mvc with url dispatched to an funciton to process
 using array to hold name of fuction, the key is url request
 then we use call_user_func to invoke
 */
$uriContext = $_SERVER["REQUEST_URI"];
$uriPathArr = explode("?", $uriContext);
$uriPath = $uriPathArr[0];
$uriQueryString = "";

if (count($uriPathArr) > 1) {
    $uriQueryString = $uriPathArr[1];
}

$requestMethod = $_SERVER["REQUEST_METHOD"];
$requestbody = file_get_contents('php://input');

class BaseRequest{
    public $urlRaw="";
    public $method="";
    public $urlPath="";
    public $urlQueryString="";
    public $body="";
    public $requestHeader=[];
    public $requestFiles=[];
}

//begin:do simple MVC
//begin:action definition
function index(BaseRequest $requests)
{
    //your real logic code
    return json_encode(["request" => $requests, "data" => "your data process, you logic do here"]);
}

function about(BaseRequest $requests)
{
    //your real logic code
    return json_encode(["about" => "Nguyen Phan Du", "version" => "1.0.0"]);
}
//end:action definition

//begin:routing register
$routingHandle = [];
$routingHandle[""] = "index";
$routingHandle["/"] = "index";
$routingHandle["/index"] = "index";
$routingHandle["/home"] = "index";
$routingHandle["/about"] = "about";

//end:routing register
//end:do simple MVC

//begin: build request context, real invoke request context, build your request context will use in actin definition
$requestContext=new BaseRequest();
$requestContext->urlRaw= $uriContext;
$requestContext->method= $requestMethod;
$requestContext->urlPath= $uriPath;
$requestContext->urlQueryString= $uriQueryString;
$requestContext->body= $requestbody;
$requestContext->requestHeader=[];
foreach (getallheaders() as $name => $value) {
    $requestContext->requestHeader[$name]=$value;
}
//https://www.php.net/manual/en/features.file-upload.php
//https://www.php.net/manual/en/reserved.variables.files.php
$requestContext->requestFiles=$_FILES;

//end: build request context

$routingExisted = array_key_exists($uriPath, $routingHandle);
if ($routingExisted) {
    $actionResult = call_user_func($routingHandle[$uriPath], $requestContext);
    http_response_code(200);
    echo $actionResult;
} else {
    http_response_code(404);
    echo "{ \"code\":\"404\", 
        \"message\":\"Not found\", 
        \"uriContext\":\"${uriContext}\",
        \"requestMethod\":\"${requestMethod}\",
        \"uriPath\":\"${uriPath}\",
        \"uriQueryString\":\"${uriQueryString}\",
        \"requestbody\":\"${requestbody}\"
        } ";
}

// //routing
// $path = pathinfo($_SERVER["SCRIPT_FILENAME"]);
// if ($path["extension"] == "el") {
//     header("Content-Type: text/x-script.elisp");
//     readfile($_SERVER["SCRIPT_FILENAME"]);
// }
// else if (preg_match('/\.(?:png|jpg|jpeg|gif)$/',$uriContext )) {
//     header("Content-Type: application/json; charset=utf-8");
//     echo ("API support only for json");
// }
// else {
    
//     header("Content-Type: application/json; charset=utf-8");
//     //echo $uriContext;
//     echo ('{"uri":"'.$uriContext.'", "message":"hello world"}'); 
// }
