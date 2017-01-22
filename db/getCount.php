<?php
 
require("db.php");
 
if(isset($_GET['floor']))
{
    $floor = $_GET['floor'];   
}
 
if(isset($_GET['room']))
{
    $room = $_GET['room']; 
}
 
 
$query = mysql_query("SELECT * FROM currant where floor = ". $floor ." and room = ". $room." ");
$num = mysql_num_rows($query);
 
for ($i = 0; $i < $num; $i++)
{
    if($data = mysql_fetch_array($query))
    {
        $count = $data['count'];       
    }
}
 
echo $count;
 
 
 
?>