<div>
	<?php if(isset($holdings)): ?>
		<!-- User has share holdings, display them here -->
		<form action="sell.php" method="post">
		<table id="holdings">
			<thead>
				<tr>
					<th>Symbol</th>
					<th>Company</th>
					<th>Quantity</th>
					<th>Price/share</th>
					<th>Value</th>
					<th>&nbsp;</th>
				</tr>
			</thead>
			<tbody>
		<?php foreach($holdings as $holding): ?>
			<tr>
				<td><?= $holding["symbol"] ?></td>
				<td><?= $holding["name"] ?></td>
				<td><?= $holding["quantity"] ?></td>
				<td><?= $holding["price"] ?></td>
				<td><?= $holding["value"] ?></td>				
				<td><button name="sell" value="<?= $holding["symbol"] ?>">Sell</button></td>
			</tr>
		<?php endforeach; ?>
		</tbody>
		</table>
		</form>
	<?php else: ?>
		<!-- User doesn't have any share holdings -->
		<div id="noholdings">
			You don't appear to have any holdings as yet... why not get a share price <a href="quote.php">now</a>?
		</div>
	<?php endif; ?>
		<div id="cash">
			You currently have <code>$<?= $cash ?></code> to burn!
		</div>
		<div id="quote">
			Get a <a href="quote.php">quote</a> and buy!
		</div>
		<div id="history">
			Additionally, check your transaction <a href="history.php">history</a>
		</div>
		<div>
			For the security-conscious, change your <a href="password.php">password</a>
		</div>
</div>
<div>
    <a href="logout.php">Log Out</a>
</div>
