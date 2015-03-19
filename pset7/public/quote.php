<?php

/**
 * quotes.php - an MVC controller, for CS50 - Problem set 7
 * Renders a view with the get_quote and show_quote templates
 */

	//Require the configuration settings
	require("../includes/config.php");
	
	if(isset($_POST["stock"]))
	{
		$stock = lookup($_POST["stock"]);
		
		if($stock === false)
		{
			apologize("Unrecognised stock symbol, maybe the spelling is wrong?");
		}
		else
		{
			$title = ["title"=>"Your quote"];
			$data = array_merge($title, $stock);
			render("show_quote.php", $data);
		}
	}
	else
	{
		render("get_quote.php", ["title"=>"Retrieve a quote"]);
	}
?>
