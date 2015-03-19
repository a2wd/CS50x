<?php

    // configuration
    require("../includes/config.php");

    // if form was submitted
    if ($_SERVER["REQUEST_METHOD"] == "POST")
    {
        //Check for errors in $_POST
        $errors = "";
        
        //Make sure a username is given
        if(empty($_POST['username']))
        {
            $errors .= "No username was given";
        }
        
        //Make sure a password was given
        if($_POST['password'] === "")
        {
        	if($errors === "")
	            $errors .= "No password was given";
	        else
	        	$errors .= " and no password was given";
        }
        //Make sure the password matches the confirmation
        else if($_POST['confirmation'] !== $_POST['password'])
        {
        	if($errors === "")
	            $errors .= "Password and confirmation must be the same";
	        else
	        	$errors .= " and also, the password doesn't match the confirmation";
        }
        
        
        //Check to see if there were any errors, else we can add user
        if($errors !== "")
        {
            //Pass errors to apology function
            $errors .= ".";
            apologize($errors);
        }
        else
        {
            //We have a username and confirmed password
            $sql_command = "INSERT INTO users (username, hash, cash)
							VALUES (?, ?, 10000)";
							
			//Execute the sql wrapper function with a hash of the password and the username
            $result = query($sql_command, $_POST["username"], crypt($_POST['password']));
            
            //Process any errors
            if($result === false)
            {
            	//Check if the username already exists
            	$sql_command = "SELECT 1 FROM users
            					WHERE username = ?";
            	$result = query($sql_command, $_POST["username"]);
            	
            	//The username exists
            	if($result === true)
            	{
            		apologize("That username already exists, try with something different");
            	}
            	//Server error
            	else
            	{
            		apologize("There was a server error, please try again later");
            	}
            }
            else
            {
            	//Success
            	$result = query("SELECT LAST_INSERT_ID() AS id");
            	if($result === false)
            	{
            		apologize("Your account was created however, there was a server error logging you in");
            	}
            	else
            	{
            		//For conciseness, unset the text field for password confirmation
            		unset($_POST["confirmation"]);
            		
            		//Login the user
            		session_start();
            		$_SESSION["id"] = $result[0]["id"];
            		
            		redirect("/");
            	}
            }
        }
        
    }
    else
    {
        // else render form
        render("register_form.php", ["title" => "Register"]);
    }

?>
