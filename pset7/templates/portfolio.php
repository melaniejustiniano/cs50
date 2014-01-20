<ul class="nav nav-pills">
    <li><a href="quote.php">Quote</a></li>
    <li><a href="buy.php">Buy</a></li>
    <li><a href="sell.php">Sell</a></li>
    <li><a href="history.php">History</a></li>
    <li><a href="logout.php"><strong>Log Out</strong></a></li>
</ul>

<table class="table table-striped">
    <thead>
        <?php            
            print("<tr>\n");
            print("<th>Symbol</th>\n");
            print("<th>Name</th>\n");
            print("<th>Shares</th>\n");
            print("<th>Price</th>\n");
            print("<th>TOTAL</th>\n");
            print("</tr>\n");
        ?>
    </thead>
    
    <tbody>
       <? 
            foreach ($rows as $row) 
            {        
                print("<tr>\n");
                print("<td>{$row["symbol"]}</td>\n");
                print("<td>{$name[$row["symbol"]]}</td>\n");
                print("<td>{$row["shares"]}</td>\n");
                print("<td>" . '$' . "{$price[$row["symbol"]]}</td>\n");
                print("<td>" . '$' . "{$total[$row["symbol"]]}</td>\n");
                print("</tr>\n");
            }
            
            print("<tr>\n");
            print("<td colspan = 4>CASH</td>\n");
            print("<td>" . '$' . "{$cash}</td>\n");
            print("</tr>\n");
            
        ?>
    </tbody>
</table>

<div>
    Change your password <a href="change.php">here</a>!
</div>
