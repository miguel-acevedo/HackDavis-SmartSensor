<?php
 
require("db.php");
 
if(isset($_GET['first']))
{
    $firstname = $_GET['first'];
    mysql_query("update people set firstname = '". $firstname ."' where id = 0");
     
}
 
if(isset($_GET['last']))
{
    $lastname = $_GET['last'];
    mysql_query("update people set lastname = '". $lastname ."' where id = 0");
     
}
 
 
$query = mysql_query("SELECT * FROM people where id = 0");
$num = mysql_num_rows($query);
 
for ($i = 0; $i < $num; $i++)
{
    if($data = mysql_fetch_array($query))
    {
        $firstname = $data['firstname'];
        $lastname = $data['lastname'];
         
    }
}
 
echo $firstname . " " . $lastname;
 
 
?>