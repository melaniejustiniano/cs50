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
            
        // enforce proper input
        if (!preg_match("/^\d+$/", $_POST["shares"])
            || $_POST["shares"] == 0)
        {
            apologize("Shares should be a positive integer!");
        }

        // make input symbol uppercase        
        $_POST["symbol"] = strtoupper($_POST["symbol"]);
        
        // find user stock information
        $rows = query("SELECT symbol, shares FROM Stocks
                       WHERE id = ?", $_SESSION["id"]);
        if ($rows === false)
            apologize("Could not find user information!");
        
        // to check if stock owned
        $checker = 0;
        
        // look through each stock user owns
        foreach ($rows as $row)
        {
            // if stock matches input stock
            if ($_POST["symbol"] == $row["symbol"])
            {
                // disallow selling more shares than owned
                if ($_POST["shares"] > $row["shares"])
                    apologize("You don't own that many shares!");
                
                // delete stock if selling all shares
                if ($_POST["shares"] == $row["shares"])
                {
                    $delete = query("DELETE FROM Stocks WHERE id = ?
                                     AND symbol = ?", $_SESSION["id"],
                                     $_POST["symbol"]);
                    
                    // denote user owned input stock
                    $checker = 1;
                }
                
                // update shares in table
                else if ($_POST["shares"] < $row["shares"])
                {  
                    $update = query("UPDATE Stocks SET shares = shares - ? 
                                     WHERE id = ? AND symbol = ?",
                                     $_POST["shares"], $_SESSION["id"],
                                     $_POST["symbol"]);
                     if ($update === false)
                        apologize("Could not update shares!");
                    
                    // denote user owned input stock
                    $checker = 1;
                }
            }
        }
        
        // if input stock not found in table
        if ($checker == 0)
            apologize("You don't own this stock!");
        
        // if found indicated by checker
        else
        {
            // lookup current stock price
            $stock = lookup($_POST["symbol"]);
            if ($stock === false)
                apologize("Could not lookup stock!");
            
            // update cash    
            $change = $stock["price"] * $_POST["shares"];                    
            $update = query("UPDATE users SET cash = cash + ? WHERE
                             id = ?", $change, $_SESSION["id"]);
            if ($update === false)
                apologize("Could not update cash!");
            
            // update history                                                
            $insert = query("INSERT INTO history(id, bought, symbol,
                             shares, price) VALUES(?, ?, ?, ?, ?)", 
                             $_SESSION["id"], "Sold", $_POST["symbol"],
                             $_POST["shares"], $stock["price"]);
            if ($insert === false)
                apologize("Could not create history!");
        }
        
        // redirect to portfolio
        redirect("/");
    }
  
    else
    {
        // else render form
        render("sell_form.php", ["title" => "Sell Stocks"]);
    }
?>
