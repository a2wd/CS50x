<?php

    // configuration
    require("../includes/config.php"); 
    
    //Find user's stocks
    $sql_command = "SELECT stock, quantity FROM shares
    				WHERE id = ?";
	$result = query($sql_command, $_SESSION["id"]);
   
	if($result === false)
	{
		// render portfolio
		render("portfolio.php", ["title" => "Portfolio"]);   
	}
	else
	{
		//Initialise holdings array to store users's shares
		$holdings = array();
		
		//Lookup each holding from the stock symbols
		foreach($result as $holding)
		{
			//Use a temporary array to store the stock information
			//and to calculate the quantity/value of the stocks
			$tmp = lookup($holding["stock"]);
			$tmp["quantity"] = number_format($holding["quantity"], 4);
			$tmp["value"] = "$" . number_format($tmp["price"] * $holding["quantity"], 2);
			$tmp["price"] = "$" . $tmp["price"];
			
			//Add this stock information to our holdings array
			$holdings[] = $tmp;
		}
		
		//Finally, check for the current cash balance
		$sql_command = "SELECT cash FROM users WHERE id = ?";
		$result = query($sql_command, $_SESSION['id']);
		
		if($result === false)
		{
			apologize("Unable to access the database, please try again later");
		}
		else
		{
			$data["cash"] = number_format($result[0]["cash"], 2);
		}
		
		//Store holdings & page title to pass to render
		$data["title"] = "Portfolio";
		$data["holdings"] = $holdings;
		
	    // render portfolio with all stock data
    	render("portfolio.php", $data);
    }

//No need to include the closing tag
