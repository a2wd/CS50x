<div>
<h2>Transaction history</h2>
<?php if(!empty($history)): ?>
	<table id="holdings">
		<thead>
			<tr>
				<th>Purchase</th>
				<th>Sale</th>
				<th>Stock</th>
				<th>Price</th>
				<th>Consideration</th>
				<th>Time & Date</th>
			</tr>
		</thead>
		<tbody>
		<?php foreach($history as $act): ?>
			<tr>
				<?php if($act["isbuy"]): ?>
					<td>&#10004;</td>				
					<td>&nbsp;</td>					
				<?php else: ?>
					<td>&nbsp;</td>					
					<td>&#10004;</td>									
				<?php endif; ?>
				<td><?= $act["symbol"] ?></td>
				<td><?= $act["price"] ?></td>
				<td><?php echo number_format($act["price"] * $act["quantity"], 2); ?></td>
				<td><?= $act["when"] ?></td>																				
			</tr>
		<?php endforeach; ?>
		</tbody>
	</table>
<?php else: ?>
	<div>
		You don't have any transactions to report of yet.
	</div>
<?php endif; ?>
</div>
<div>
	Go back <a href="index.php">home</a>
</div>
