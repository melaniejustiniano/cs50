<?php

    // configuration
    require("../includes/config.php");
    
    // if form was submitted
    if ($_SERVER["REQUEST_METHOD"] == "POST")
    {
        // if fields empty
        if($_POST["symbol"] == NULL)
            apologize("Empty symbol field!");
        if($_POST["shares"] == NULL)
            apologize("Empty shares field!");

        // disallow improper input
        if (!preg_match("/^\d+$/", $_POST["shares"]) || $_POST["shares"] == 0)
            apologize("Shares should be a positive integer!");
        
        // make input symbol uppercase
        $_POST["symbol"] = strtoupper($_POST["symbol"]);
        
        // lookup stock information for cash and history
        $stock = lookup($_POST["symbol"]);
        if ($stock === false)
            apologize("Could not look up stock! \n");

        // find cost
        $cost = $_POST["shares"] * $stock["price"];

        // find cash in user information
        $rows = query("SELECT cash FROM users WHERE id = ?",
                       $_SESSION["id"]);
        if ($rows === false)
            apologize("Could not find user information!");
        
        // disallow spending more than cost              
        foreach ($rows as $row)
        {
            if ($cost > $row["cash"])
                apologize("You don't have enough money!");
        }
        
        // create or change table value for stocks
        $insert = query("INSERT INTO Stocks (id, symbol, shares) VALUES
                         (?, ?, ?) ON DUPLICATE KEY UPDATE shares = 
                         shares + ?", $_SESSION["id"], $_POST["symbol"], 
                         $_POST["shares"], $_POST["shares"]);
        if ($insert === false)
            apologize("Could not buy stock!");
         
        // update cash    
        $update = query("UPDATE users SET cash = cash - ? WHERE
                         id = ?", $cost, $_SESSION["id"]);
        if ($update === false)
            apologize("Could not update cash!");
        
        // create history
        $insert = query("INSERT INTO history(id, bought, symbol, shares, price)
                         VALUES(?, ?, ?, ?, ?)", $_SESSION["id"], "Bought",
                         $_POST["symbol"], $_POST["shares"], $stock["price"]);
        if ($insert === false)
            apologize("Could not create history!");
        
        // redirect to index    
        redirect("/");
    }
  
    else
    {
        // else render form
        render("buy_form.php", ["title" => "Buy Stocks"]);
    }
?>
