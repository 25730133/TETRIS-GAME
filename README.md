# Tetris Game

## 1. Giới thiệu đề tài

Tetris là một trò chơi điện tử thuộc thể loại giải đố, trong đó người chơi điều khiển các khối hình học gọi là Tetrimino rơi từ phía trên xuống trong một không gian hai chiều. Nhiệm vụ chính của người chơi là di chuyển, xoay và sắp xếp các khối sao cho lấp đầy các hàng ngang. Khi một hàng được lấp đầy hoàn toàn, hàng đó sẽ bị xóa và các khối phía trên sẽ rơi xuống.

Đề tài Tetris được lựa chọn vì trò chơi có luật chơi đơn giản nhưng yêu cầu tư duy logic, khả năng quan sát và phản xạ nhanh. Về mặt lập trình, Tetris là một đề tài phù hợp để áp dụng các kiến thức cơ bản như xử lý ma trận hai chiều, điều khiển đối tượng, kiểm tra va chạm, cập nhật trạng thái trò chơi và xây dựng vòng lặp game.

Thông qua đề tài này, nhóm có cơ hội rèn luyện kỹ năng lập trình, tư duy giải quyết vấn đề và khả năng phối hợp trong quá trình xây dựng một sản phẩm phần mềm hoàn chỉnh.

## 2. Giới thiệu nhóm thực hiện

| Thành viên | MSSV | Vai trò | Nhiệm vụ chính |
|---|---|---|---|
| Lê Công Phú | 25730133 | SV1 | Xây dựng code nền, thiết lập Git, tạo cấu trúc chương trình và khởi tạo board. |
| Hoàng Minh Anh | 25730096 | SV2 | Xây dựng chức năng xóa dòng `removeLine`, xử lý các hàng đầy và cập nhật lại ma trận. |
| Nguyễn Thị Xuân Tiên | 25730152 | SV3 | Cải tiến giao diện hiển thị, chỉnh sửa viền và block từ dạng hình chữ nhật sang hình vuông. |
| Đỗ Cao Quỳnh Lan | 25730121 | SV4 | Xử lý chức năng xoay khối và đảm bảo tính hợp lệ thông qua kiểm tra va chạm. |
| Lê Anh Tuấn | 25730158 | SV5 | Xây dựng cơ chế tăng tốc độ trò chơi sau mỗi lần xóa dòng. |
| Cả nhóm |  | Phối hợp thực hiện | Cùng trao đổi, chỉnh sửa, thống nhất nội dung và hoàn thiện bài trên LaTeX. |

## 3. Các bước nhóm thực hiện

Quá trình thực hiện trò chơi Tetris được chia thành các bước chính sau:

### Bước 1: Xây dựng nền tảng chương trình

Nhóm bắt đầu bằng việc thiết lập cấu trúc chương trình, tạo project ban đầu và khởi tạo bảng chơi. Bảng chơi được xây dựng dưới dạng ma trận hai chiều, trong đó mỗi ô biểu thị một vị trí trong không gian game.

Các công việc chính gồm:

- Tạo cấu trúc code ban đầu.
- Thiết lập Git và GitHub để quản lý mã nguồn.
- Khởi tạo board trò chơi.
- Xác định kích thước và giới hạn của khu vực chơi.

### Bước 2: Xây dựng cơ chế điều khiển khối

Sau khi có nền tảng ban đầu, nhóm tiếp tục xây dựng chức năng điều khiển khối Tetrimino. Người chơi có thể di chuyển khối sang trái, sang phải, đi xuống hoặc xoay khối để lựa chọn vị trí phù hợp.

Các thao tác điều khiển chính:

| Phím | Chức năng |
|---|---|
| `A` | Di chuyển khối sang trái |
| `D` | Di chuyển khối sang phải |
| `W` | Xoay khối |
| `S` | Làm khối rơi nhanh hơn |

### Bước 3: Xử lý va chạm

Nhóm xây dựng cơ chế kiểm tra va chạm để đảm bảo khối không đi xuyên qua biên, không vượt khỏi bảng chơi và không chồng lên các khối đã cố định.

Cơ chế va chạm được áp dụng trong các trường hợp:

- Khối chạm biên trái hoặc biên phải.
- Khối chạm đáy bảng chơi.
- Khối va chạm với các khối đã được cố định trước đó.
- Khối sau khi xoay vẫn phải nằm trong vị trí hợp lệ.

### Bước 4: Xây dựng chức năng xóa dòng

Chức năng xóa dòng là một trong những cơ chế quan trọng nhất của trò chơi Tetris. Khi một hàng ngang được lấp đầy hoàn toàn, hệ thống sẽ xóa hàng đó và cập nhật lại ma trận bằng cách dịch các hàng phía trên xuống.

Nguyên lý xử lý:

```text
Kiểm tra từng hàng trong bảng chơi
Nếu một hàng đã đầy:
    Xóa hàng đó
    Dịch các hàng phía trên xuống
    Cập nhật lại ma trận trò chơi
