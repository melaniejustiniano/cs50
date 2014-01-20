<?php

    // configuration
    require("../includes/config.php"); 
    
    // collect user's stock information
    $rows = query("SELECT symbol, shares FROM Stocks
                   wHERE id = ?", $_SESSION["id"]);
    if ($rows === false)
        apologize("Couldn't find stock information!");        

    // initialize empty array for table values        
    // not a table because variable names too long
    $name = array("0");
    $price = array("0");
    $total = array("0");
    $cash = array("0");
    
    // look through different stocks and set values
    foreach ($rows as $row)
    {   
        $stock = lookup($row["symbol"]);
        if ($stock === false)
            apologize("Could not lookup stock!");

        $name[$row["symbol"]] = $stock["name"];
        $price[$row["symbol"]] = number_format($stock["price"], 2);
        $total[$row["symbol"]] = $price[$row["symbol"]] * $row["shares"];
        $total[$row["symbol"]] = number_format($total[$row["symbol"]], 2);
    }
    
    // change cash to proper decimals    
    $users = query("SELECT cash FROM users where id = ?", $_SESSION["id"]);
    if ($users === false)
        apologize("Could not find user information!");
    
    foreach ($users as $user)
        $cash = number_format($user["cash"], 2);
      
    // render portfolio
    render("portfolio.php", ["title" => "Portfolio", "rows" => $rows,
            "name" => $name, "price" => $price, "total" => $total,
            "cash" => $cash]);

?>
