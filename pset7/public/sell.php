<?php

	//Sell.php - sell all of a stock
	//Pset7 / CS50
	
    // configuration
    require("../includes/config.php"); 
    
    if(!isset($_POST))
    {
    	apologize("You didn't select something to sell!");
    }
    
    //If the user just clicked the sell button, give them a confirmation price
    if(isset($_POST["sell"]))
    {
    	//First check they own this stock!
    	$sql_command = "SELECT quantity FROM shares 
    					WHERE id = ?
    					AND stock = ?";
    	$result = query($sql_command, $_SESSION["id"], $_POST["sell"]);
    	
    	if($result === false)
    	{
    		apologize("You don't have any of that stock to sell!");
    	}
    	else
    	{
    		//Give the user a confirmation of the price of the stock
    		$quote = lookup($_POST["sell"]);
    		if($quote === false)
    		{
    			apologize("Sorry, we couldn't retrieve that stock's price, please try again later");
    		}
    		else
    		{
    			//Collate the data and pass to render
    			$data["value"] = "$" . number_format($quote["price"] * $result[0]["quantity"], 2);
    			$data["price"] = "$" . number_format($quote["price"], 2);
    			$data["quantity"] = number_format($result[0]["quantity"], 4);
    			$data["stock"] = $_POST["sell"];
    			$data["name"] = $quote["name"];
    			render("sell_confirm.php", ["title"=>"Confirmation quote", "quote"=>$data]);
    		}
    	}
    }
    else if(isset($_POST["confirm"]))
    {
    	//The user wants to sell this stock.
    	//First check they own this stock!
    	$sql_command = "SELECT quantity FROM shares 
    					WHERE id = ?
    					AND stock = ?";
    	$result = query($sql_command, $_SESSION["id"], $_POST["confirm"]);
    	if($result === false)
    	{
    		apologize("You don't have any of that stock to sell!");
    	}
    	else
    	{    		
    		//Check the price of the stock
    		$quote = lookup($_POST["confirm"]);
    		if($quote === false)
    		{
    			apologize("Sorry, we couldn't retrieve that stock's price, please try again later");
    		}
    		else
    		{
    			//Finally sell the stock!
    			
    			//Check the amount to be made
	   			$amount = 0.0;
    			foreach($result as $result_single)
    			{
    				$amount = $result_single["quantity"];
    			}		
    			$gain = $amount * $quote["price"];
    			
    			//Execute the delete
    			$sql_command = "DELETE FROM shares
    							WHERE id= ?
    							AND stock = ?";
    			$result = query($sql_command, $_SESSION["id"], $_POST["confirm"]);
    			
    			//There was a problem deleting the stocks
    			if($result === false)
    			{
    				apologize("Unable to sell that share at this time, please try again later");
    			}
    			
    			//Update cash holdings
    			$sql_command = "UPDATE users
    							SET cash = cash + ?
    							WHERE id= ?";
    			$result = query($sql_command, $gain, $_SESSION["id"]);    							
    			
    			//There was a problem adding the cash from the sale
    			if($result === false)
    			{
    				apologize("Unable to give you your money. We'll take that and run, thanks");
    			}

				//Log the buy in user's history
				$sql_command = "INSERT INTO history
								(id, quantity, symbol, price, isbuy)
								VALUES (?, ?, ?, ?, false)";
				$result = query($sql_command,
					$_SESSION["id"],
					$amount,
					$_POST["confirm"],
					$quote["price"]
				);
				
				if($result === false)
				{
					apologize("Unable to log your sale into your history");
				}    			

				//Finally, check for the current cash balance
				$sql_command = "SELECT cash FROM users WHERE id = ?";
				$result = query($sql_command, $_SESSION['id']);
				$cash = "";
				if($result === false)
				{
					apologize("Unable to access the database, please try again later");
				}
				else
				{
					$cash = number_format($result[0]["cash"], 2);
				}    			
    			
    			//Put together data to pass to render function
    			$data = array();
    			$data["quantity"] = number_format($amount, 4);
    			$data["value"] = "$" . number_format($gain, 2);
    			$data["name"] = $quote["name"];
    			render("sell_success.php",["title"=>"Stocks sold", "details"=>$data, "cash"=>$cash]);
    		}
    	}
    }
    else
    {
    	redirect("index.php");
    }

//No need to include the closing tag
