# Tetris Game

## 1. Tổng quan dự án

Dự án này là phiên bản console của trò chơi Tetris cổ điển. Người chơi sẽ điều khiển các khối hình học Tetrimino rơi xuống trong một bảng hai chiều và sắp xếp chúng để tạo thành các hàng ngang hoàn chỉnh. Khi một hàng được lấp đầy, hàng đó sẽ bị xóa khỏi bảng và người chơi tiếp tục cho đến khi không còn chỗ để tạo khối mới.

Dự án tập trung vào các kiến thức cơ bản trong phát triển game như xử lý ma trận hai chiều, điều khiển thời gian thực bằng bàn phím, kiểm tra va chạm, di chuyển và xoay khối, xóa dòng hoàn chỉnh và cập nhật trạng thái trò chơi liên tục.

Mặc dù trò chơi được xây dựng trên giao diện console đơn giản, dự án vẫn thể hiện đầy đủ logic cốt lõi của một hệ thống game tương tác thời gian thực.

## 2. Chức năng chính

- Tạo ngẫu nhiên các khối Tetrimino
- Di chuyển khối sang trái, phải và xuống dưới
- Xoay khối khi đang rơi
- Kiểm tra va chạm với biên và các khối cố định
- Xóa các dòng hoàn chỉnh
- Cập nhật bảng trò chơi liên tục
- Kết thúc trò chơi khi không còn chỗ cho khối mới

## 3. Gameplay và điều khiển

Trò chơi hoạt động theo nguyên tắc cơ bản của Tetris. Một khối sẽ xuất hiện ở phía trên bảng và tự động rơi xuống theo thời gian. Người chơi có thể di chuyển hoặc xoay khối trước khi nó chạm đáy hoặc va vào khối khác.

Khi khối không thể tiếp tục rơi xuống, nó sẽ được cố định vào bảng. Nếu một hàng ngang được lấp đầy hoàn toàn, hàng đó sẽ bị xóa và các hàng phía trên sẽ dịch xuống.

Trò chơi tiếp tục tạo khối mới cho đến khi bảng đầy.

### Điều khiển

| Phím | Chức năng |
|---|---|
| A / a | Di chuyển sang trái |
| D / d | Di chuyển sang phải |
| W / w | Xoay khối |
| S / s | Tăng tốc độ rơi |
| X / x | Di chuyển xuống |
| Q / q | Thoát trò chơi |

## 4. Quy trình hoạt động cơ bản

1. Khởi động trò chơi
2. Tạo khối mới
3. Nhận thao tác từ người chơi
4. Kiểm tra va chạm
5. Cập nhật vị trí khối
6. Cố định khối khi không thể rơi tiếp
7. Xóa các dòng hoàn chỉnh
8. Tạo khối tiếp theo
9. Lặp lại cho đến khi Game Over

## 5. Thành viên nhóm và phân công nhiệm vụ

| STT | Thành viên | MSSV | Vai trò | Nhiệm vụ trọng tâm |
|---|---|---|---|---|
| 1 | Lê Công Phú | 25730133 | SV1 | Trưởng nhóm kỹ thuật: xây dựng code nền, thiết lập Git, khởi tạo board. |
| 2 | Hoàng Minh Anh | 25730096 | SV2 | Phụ trách xử lý dữ liệu trò chơi và báo cáo: xử lý chức năng `removeLine`, cập nhật ma trận; xây dựng nội dung và biên soạn các report. |
| 3 | Nguyễn Thị Xuân Tiên | 25730152 | SV3 | Phụ trách giao diện người dùng và LaTeX: cải tiến giao diện, chỉnh sửa viền và khối vuông; code và định dạng tài liệu bằng LaTeX. |
| 4 | Đỗ Cao Quỳnh Lan | 25730121 | SV4 | Phụ trách logic xoay khối: xử lý xoay khối và kiểm tra va chạm. |
| 5 | Lê Anh Tuấn | 25730158 | SV5 | Phụ trách tốc độ rơi và kiểm thử: xây dựng cơ chế tăng tốc sau mỗi lần xóa dòng, hỗ trợ kiểm thử chương trình. |
