<ul class="nav nav-pills">
    <li><a href="quote.php">Quote</a></li>
    <li><a href="buy.php">Buy</a></li>
    <li><a href="sell.php">Sell</a></li>
    <li><a href="history.php">History</a></li>
    <li><a href="logout.php"><strong>Log Out</strong></a></li>
</ul>

<table class="table table-striped">
    <thead>
        <?  
            print("<tr>\n");
            print("<th>Symbol</th>\n");
            print("<th>Bought/Sold</th>\n");
            print("<th>Shares</th>\n");
            print("<th>Price</th>\n");
            print("<th>Time</th>\n");
            print("</tr>\n");
        ?>
    </thead>
    <tbody> 
        <?
            foreach($rows as $row)
            {
                print("<tr>\n");
                print("<td>{$row["symbol"]}</td>\n");
                print("<td>{$row["bought"]}</td>\n");
                print("<td>{$row["shares"]}</td>\n");
                print("<td>" . '$' . "{$row["price"]}</td>\n");
                print("<td>{$row["time"]}</td>\n");
                print("</tr>");
            }
        ?>
    </tbody>
</table>
