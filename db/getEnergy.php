<?php
require("db.php");

$return_arr = array();

$building = $_GET['building']; // Name of the building your trying to get data from.

$query = mysql_query("SELECT * FROM energy where type='".$building."'"); 

$num = mysql_num_rows($query);
 
for ($i = 0; $i < $num; $i++)
{
    if($data = mysql_fetch_array($query))
    {
		$row_array['time'] = $data['time'];
		$row_array['power'] = $data['power'];

		array_push($return_arr,$row_array);      
    }
}

echo json_encode($return_arr);

?>